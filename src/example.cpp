#include "eiface.h"
#include "engine/iserverplugin.h"
#include "igameevents.h"
#include "tier1/tier1.h"
#include "tier2/tier2.h"
#include "tier3/tier3.h"

//---------------------------------------------------------------------------------
// Purpose: a sample 3rd party plugin class
//---------------------------------------------------------------------------------
class CEmptyServerPlugin : public IServerPluginCallbacks {
public:
  CEmptyServerPlugin();
  ~CEmptyServerPlugin();

  // IServerPluginCallbacks methods
  virtual bool Load(CreateInterfaceFn interfaceFactory,
                    CreateInterfaceFn gameServerFactory);
  virtual void Unload(void);
  virtual void Pause(void){};
  virtual void UnPause(void){};
  virtual const char *GetPluginDescription(void);
  virtual void LevelInit(char const *pMapName){};
  virtual void ServerActivate(edict_t *pEdictList, int edictCount,
                              int clientMax){};
  virtual void GameFrame(bool simulating){};
  virtual void LevelShutdown(void){};
  virtual void ClientActive(edict_t *pEntity){};
  virtual void ClientDisconnect(edict_t *pEntity){};
  virtual void ClientPutInServer(edict_t *pEntity, char const *playername){};
  virtual void SetCommandClient(int index){};
  virtual void ClientSettingsChanged(edict_t *pEdict){};

  virtual PLUGIN_RESULT ClientConnect(bool *bAllowConnect, edict_t *pEntity,
                                      const char *pszName,
                                      const char *pszAddress, char *reject,
                                      int maxrejectlen) {
    return PLUGIN_CONTINUE;
  };
  virtual PLUGIN_RESULT ClientCommand(edict_t *pEntity, const CCommand &args) {
    return PLUGIN_CONTINUE;
  };
  virtual PLUGIN_RESULT NetworkIDValidated(const char *pszUserName,
                                           const char *pszNetworkID) {
    return PLUGIN_CONTINUE;
  };
  virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie,
                                        edict_t *pPlayerEntity,
                                        EQueryCvarValueStatus eStatus,
                                        const char *pCvarName,
                                        const char *pCvarValue){};

  // added with version 3 of the interface.
  virtual void OnEdictAllocated(edict_t *edict){};
  virtual void OnEdictFreed(const edict_t *edict){};
};

//
// The plugin is a static singleton that is exported as an interface
//
CEmptyServerPlugin g_EmptyServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CEmptyServerPlugin, IServerPluginCallbacks,
                                  INTERFACEVERSION_ISERVERPLUGINCALLBACKS,
                                  g_EmptyServerPlugin);

//---------------------------------------------------------------------------------
// Purpose: constructor/destructor
//---------------------------------------------------------------------------------
CEmptyServerPlugin::CEmptyServerPlugin() {}

CEmptyServerPlugin::~CEmptyServerPlugin() {}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is loaded, load the interface we need from
// the engine
//---------------------------------------------------------------------------------
bool CEmptyServerPlugin::Load(CreateInterfaceFn interfaceFactory,
                              CreateInterfaceFn gameServerFactory) {
  ConnectTier1Libraries(&interfaceFactory, 1);
  ConnectTier2Libraries(&interfaceFactory, 1);
  ConnectTier3Libraries(&interfaceFactory, 1);

  MathLib_Init(2.2f, 2.2f, 0.0f, 2);
  ConVar_Register(0);
  return true;
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unloaded (turned off)
//---------------------------------------------------------------------------------
void CEmptyServerPlugin::Unload(void) {
  ConVar_Unregister();
  DisconnectTier3Libraries();
  DisconnectTier2Libraries();
  DisconnectTier1Libraries();
}

//---------------------------------------------------------------------------------
// Purpose: the name of this plugin, returned in "plugin_print" command
//---------------------------------------------------------------------------------
const char *CEmptyServerPlugin::GetPluginDescription(void) { return "Empty"; }
