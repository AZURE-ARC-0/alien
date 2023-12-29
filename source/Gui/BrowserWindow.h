#pragma once

#include <chrono>

#include "Base/Hashes.h"
#include "EngineInterface/Definitions.h"

#include "AlienWindow.h"
#include "BrowserSimulationData.h"
#include "RemoteSimulationData.h"
#include "UserData.h"
#include "Definitions.h"

class _BrowserWindow : public _AlienWindow
{
public:
    _BrowserWindow(
        SimulationController const& simController,
        NetworkController const& networkController,
        StatisticsWindow const& statisticsWindow,
        Viewport const& viewport,
        TemporalControlWindow const& temporalControlWindow,
        EditorController const& editorController);
    ~_BrowserWindow();

    void registerCyclicReferences(LoginDialogWeakPtr const& loginDialog, UploadSimulationDialogWeakPtr const& uploadSimulationDialog);

    void onRefresh();

private:
    void refreshIntern(bool withRetry);

    void processIntern() override;
    void processBackground() override;

    void processSimulationList();
    void processGenomeList();
    void processUserList();

    void processStatus();
    void processFilter();
    void processToolbar();

    void processEmojiWindow();
    void processEmojiButton(int emojiType);
    void processEmojiList(BrowserSimulationData const& sim);

    void processActionButtons(BrowserSimulationData const& sim);

    void processShortenedText(std::string const& text, bool bold = false);
    bool processActionButton(std::string const& text);
    bool processDetailButton();

    void processActivated() override;

    void sortRemoteSimulationData(std::vector<RemoteSimulationData>& remoteData, ImGuiTableSortSpecs* sortSpecs);
    void sortUserList();

    void onDownloadItem(BrowserSimulationData const& sim);
    void onDeleteItem(BrowserSimulationData const& sim);
    void onToggleLike(BrowserSimulationData const& sim, int emojiType);
    void openWeblink(std::string const& link);

    bool isLiked(std::string const& simId);
    std::string getUserNamesToEmojiType(std::string const& simId, int emojiType);

    void pushTextColor(BrowserSimulationData const& entry);
    void calcFilteredSimulationAndGenomeLists();

    DataType _selectedDataType = DataType_Simulation; 
    bool _scheduleRefresh = false;
    bool _scheduleCreateBrowserData = false;
    std::string _filter;
    bool _showCommunityCreations = false;
    float _userTableWidth = 0;
    std::unordered_set<std::string> _selectionIds;
    std::unordered_map<std::string, int> _ownEmojiTypeBySimId;
    std::unordered_map<std::pair<std::string, int>, std::set<std::string>> _userNamesByEmojiTypeBySimIdCache;

    int _numSimulations = 0;
    int _numGenomes = 0;
    std::vector<RemoteSimulationData> _rawRemoteDataList;
    std::vector<RemoteSimulationData> _filteredRemoteSimulationList;
    std::vector<RemoteSimulationData> _filteredRemoteGenomeList;

    std::vector<BrowserSimulationData> _browserSimulationList;
    std::vector<BrowserSimulationData> _browserGenomeList;

    std::vector<UserData> _userList;

    std::vector<TextureData> _emojis;

    bool _activateEmojiPopup = false;
    bool _showAllEmojis = false;
    BrowserSimulationData _simOfEmojiPopup;

    std::optional<std::chrono::steady_clock::time_point> _lastRefreshTime;

    SimulationController _simController;
    NetworkController _networkController;
    StatisticsWindow _statisticsWindow;
    Viewport _viewport;
    TemporalControlWindow _temporalControlWindow;
    LoginDialogWeakPtr _loginDialog;
    EditorController _editorController;
    UploadSimulationDialogWeakPtr _uploadSimulationDialog;
};
