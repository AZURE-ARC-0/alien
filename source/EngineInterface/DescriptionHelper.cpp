#include "DescriptionHelper.h"

#include <boost/range/adaptor/indexed.hpp>

#include "Base/NumberGenerator.h"
#include "Base/Math.h"
#include "SpaceCalculator.h"

void DescriptionHelper::duplicate(ClusteredDataDescription& data, IntVector2D const& origSize, IntVector2D const& size)
{
    ClusteredDataDescription result;

    for (int incX = 0; incX < size.x; incX += origSize.x) {
        for (int incY = 0; incY < size.y; incY += origSize.y) {
            for (auto cluster : data.clusters) {
                auto origPos = cluster.getClusterPosFromCells();
                RealVector2D clusterPos = {origPos.x + incX, origPos.y + incY};
                if (clusterPos.x < size.x && clusterPos.y < size.y) {
                    for (auto& cell : cluster.cells) {
                        cell.pos = RealVector2D{cell.pos.x + incX, cell.pos.y + incY};
                    }
                    makeValid(cluster);
                    result.addCluster(cluster);
                }
            }
            for (auto particle : data.particles) {
                auto origPos = particle.pos;
                particle.pos = RealVector2D{origPos.x + incX, origPos.y + incY};
                if (particle.pos.x < size.x && particle.pos.y < size.y) {
                    particle.setId(NumberGenerator::getInstance().getId());
                    result.addParticle(particle);
                }
            }
        }
    }
    data = result;
}

void DescriptionHelper::reconnectCells(std::vector<CellDescription>& cells, float maxdistance)
{
    std::unordered_map<int, std::unordered_map<int, std::vector<int>>> cellIndicesBySlot;

    for (auto& [index, cell] : cells | boost::adaptors::indexed(0)) {
        cell.connections.clear();
        cellIndicesBySlot[toInt(cell.pos.x)][toInt(cell.pos.y)].emplace_back(toInt(index));
    }
    for (auto& cell : cells) {
        
    }
}

void DescriptionHelper::correctConnections(ClusteredDataDescription& data, IntVector2D const& worldSize)
{
//     SpaceCalculator spaceCalculator(worldSize);
    auto threshold = std::min(worldSize.x, worldSize.y) /3;
    std::unordered_map<uint64_t, CellDescription&> cellById;
    for (auto& cluster : data.clusters) {
        for (auto& cell : cluster.cells) {
            cellById.emplace(cell.id, cell);
        }
    }
    for (auto& cluster : data.clusters) {
        for (auto& cell: cluster.cells) {
            std::vector<ConnectionDescription> newConnections;
            float angleToAdd = 0;
            for (auto connection : cell.connections) {
                auto& connectingCell = cellById.at(connection.cellId);
                if (/*spaceCalculator.distance*/Math::length(cell.pos - connectingCell.pos) > threshold) {
                    angleToAdd += connection.angleFromPrevious;
                } else {
                    connection.angleFromPrevious += angleToAdd;
                    angleToAdd = 0;
                    newConnections.emplace_back(connection);
                }
            }
            cell.connections = newConnections;
        }
    }
}

void DescriptionHelper::colorize(ClusteredDataDescription& data, std::vector<int> const& colorCodes)
{
    for (auto& cluster : data.clusters) {
        auto color = colorCodes[NumberGenerator::getInstance().getRandomInt(toInt(colorCodes.size()))];
        for (auto& cell : cluster.cells) {
            cell.metadata.color = color;
        }
    }
}

void DescriptionHelper::makeValid(ClusterDescription& cluster)
{
    auto& numberGen = NumberGenerator::getInstance();
    cluster.id = numberGen.getId();
    std::unordered_map<uint64_t, uint64_t> newByOldIds;
    for (auto& cell : cluster.cells) {
        uint64_t newId = numberGen.getId();
        newByOldIds.insert_or_assign(cell.id, newId);
        cell.id = newId;
    }

    for (auto& cell : cluster.cells) {
        for (auto& connection : cell.connections) {
            connection.cellId = newByOldIds.at(connection.cellId);
        }
    }
}

uint64_t DescriptionHelper::getId(CellOrParticleDescription const& entity)
{
    if (std::holds_alternative<CellDescription>(entity)) {
        return std::get<CellDescription>(entity).id;
    }
    return std::get<ParticleDescription>(entity).id;
}

RealVector2D DescriptionHelper::getPos(CellOrParticleDescription const& entity)
{
    if (std::holds_alternative<CellDescription>(entity)) {
        return std::get<CellDescription>(entity).pos;
    }
    return std::get<ParticleDescription>(entity).pos;
}

std::vector<CellOrParticleDescription> DescriptionHelper::getEntities(
    DataDescription const& data)
{
    std::vector<CellOrParticleDescription> result;
    for (auto const& particle : data.particles) {
        result.emplace_back(particle);
    }
    for (auto const& cell : data.cells) {
        result.emplace_back(cell);
    }
    return result;
}
