// This header is an unofficial, community-created reverse-engineered interface
// to Star Trek: Armada. It is not affiliated with, endorsed by, or officially
// released by Activision or its licensors.

#pragma once

#define IMPORTME __declspec(dllimport)

//
// Forward Declarations
//

class IMPORTME character;

// Undefined
class EULER;
class Matrix34;
class list_cell;

template <class T>
class Pointer_Pool;

struct _iobuf;

//
// Enumerated Types
//

enum AiCommand;
enum PathType;
enum EntityType;

namespace BridgeDisplay
{
    enum BridgeType
    {
        Avenger,
        Enterprise,
        Klingon,
        Romulan,
        Borg,
    };
}

namespace SpecialFlag
{
    enum Restriction;
}

namespace Team
{
    enum TeamRelation;
}

//
// Reconstructed class definitions
//

class Vector2
{
public:
    float x;
    float y;
};

class Vector3
{
public:
    float x;
    float y;
    float z;
};

//
// Class Imports
//

class IMPORTME linked_list
{
public:
    linked_list();
    ~linked_list();

    static void* operator new(unsigned int);
    static void operator delete(void*);

    linked_list& operator=(const linked_list&);

    list_cell* Add_Data(void*);
    int Already_In_List(void*);
    list_cell* Append_Data(void*);
    void Append_Whole_List(linked_list*);
    void Empty();
    void Init();
    list_cell* Random_Access_Lookup(int);
    void Remove_Cell(list_cell*);
    int Remove_Data(void*);
    int Remove_Data_Multiple(void*);
    list_cell* Return_Cell_By_Number(int);
    void* Return_Data_By_Number(int);
    int Return_Index_Of_Data(void*);

    static Pointer_Pool<linked_list>* s_linked_list_pool;
};

class IMPORTME variable_list
{
public:
    variable_list();
    ~variable_list();

    variable_list& operator=(const variable_list&);

    void update();
};

class IMPORTME timer_list
{
public:
    timer_list();
    ~timer_list();

    timer_list& operator=(const timer_list&);

    void update(float);
};

class IMPORTME unique_ID_list
{
public:
    unique_ID_list();
    ~unique_ID_list();

    unique_ID_list& operator=(const unique_ID_list&);

    list_cell* Add_Data(void*);
    void* Return_Data_By_ID(int);
};

class IMPORTME queue
{
public:
    queue();
    ~queue();

    queue& operator=(const queue&);

    void* Pop_First_In_Data();
};

class IMPORTME parameter
{
public:
    parameter& operator=(const parameter&);
};

class IMPORTME rule
{
public:
    rule(char*);
    rule();
    ~rule();

    rule& operator=(const rule&);
};

class IMPORTME IIIE
{
public:
    IIIE(int);
    IIIE(void);
    ~IIIE();

    IIIE& operator=(const IIIE&);

    void add_rule_to_affected_list(rule*);
    void choose_a_satisfied_rule();

    rule* create_rule(
        int(__cdecl*)(character&),
        void(__cdecl*)(character&),
        char*
    );

    rule* __thiscall create_rule(
        int(__cdecl* condition)(void),
        void(__cdecl* action)(void),
        char* name
    );

    void evaluate();
    void fire_all_satisfied_rules();
    void fire_the_current_rule();
    void trash_affected_list();
    void trash_rule(char*);
    void trash_rule(rule*);
    
private:
    void Fire_A_Rule(rule*);
};

class IMPORTME group
{
public:
    group(char*);
    ~group();

    group& operator=(const group&);

    void add_group_entry_function(
        void(__cdecl*)(character&),
        void(__cdecl*)(character&)
    );
    
    void remove_group_entry_function(
        void(__cdecl*)(character&),
        void(__cdecl*)(character&)
    );
    
    void add_unit_to_group(character&);
    void remove_unit_from_group(character&);

private:
    void add_group_rules_to_unit(character&);
    void remove_group_rules_from_unit(character&);
};

class IMPORTME script
{
public:
    script();
    ~script();

    script& operator=(const script&);

    void add_character_param(character*);
    void add_int_param(int);
    void add_step(int(__cdecl*)(script*));
    int execute_next_step();
    void* nth_param_ptr(int);
};

class IMPORTME character
{
    char _unknown[56];

public:
    character(const character&);
    character(char*, EntityType);
    ~character();

    character& operator=(const character&);

    void Add_Group_Membership(group*);
    void Remove_Group_Membership(group*);

    void clear_scripts();
    void execute_scripts();
    script* new_script(char*);

    IIIE _rule_factory; // not sure what "IIIE" means but it creates "rules"
};

class IMPORTME step
{
public:
    step& operator=(const step&);

    void execute(script*);
};

class IMPORTME hot_type
{
public:
    hot_type(const hot_type&);
    hot_type();

    virtual ~hot_type();

    hot_type& operator=(const hot_type&);

    virtual void add_dependent_rule(rule*);
    virtual void construct_affected_rules_lists();
    virtual short is_dirty();
    virtual void mark_dirty();
    virtual void remove_dependent_rule(rule*);
    virtual void set_clean();
};

class IMPORTME hot_float : public hot_type
{
public:
    hot_float(const hot_float&);
    hot_float(char*);
    hot_float();

    virtual ~hot_float();

    hot_float& operator=(const hot_float&);
    void operator=(float);
    operator float();

    short get(float&);
    void set(float);
};

class IMPORTME hot_int : public hot_type
{
public:
    hot_int(const hot_int&);
    hot_int(char*);
    hot_int();

    virtual ~hot_int();

    hot_int& operator=(const hot_int&);
    void operator=(int);
    operator int();

    int get(int&);
    void set(int);
};

class IMPORTME dirty_int : public hot_int
{
public:
    dirty_int(const dirty_int&);
    dirty_int(char*);
    dirty_int();

    virtual ~dirty_int();

    dirty_int& operator=(const dirty_int&);

    virtual short is_dirty();
    virtual void set_clean();
};

class IMPORTME timer_int : public hot_int
{
public:
    timer_int(const timer_int&);
    timer_int(char*);
    timer_int();

    virtual ~timer_int();

    timer_int& operator=(const timer_int&);

    virtual void set_clean();
    virtual void start(float);
    virtual void stop();
    virtual float time();
    virtual void update(float);
};

//
// Data Imports
//

extern IMPORTME linked_list load_scripts;
extern IMPORTME linked_list save_scripts;
extern IMPORTME timer_list timers;
extern IMPORTME group AI_Medium;
extern IMPORTME character WORLD;
extern IMPORTME character** robot;
extern IMPORTME hot_float strength_team_1;
extern IMPORTME hot_float strength_team_2;
extern IMPORTME hot_float strength_team_3;
extern IMPORTME hot_float strength_team_4;
extern IMPORTME hot_float strength_team_5;
extern IMPORTME hot_float strength_team_6;
extern IMPORTME hot_float strength_team_7;
extern IMPORTME hot_float strength_team_8;
extern IMPORTME hot_int isCineractiveCancel;
extern IMPORTME hot_int isCineractiveDone;
extern IMPORTME hot_int moons_team_1;
extern IMPORTME hot_int moons_team_2;
extern IMPORTME hot_int moons_team_3;
extern IMPORTME hot_int moons_team_4;
extern IMPORTME hot_int moons_team_5;
extern IMPORTME hot_int moons_team_6;
extern IMPORTME hot_int moons_team_7;
extern IMPORTME hot_int moons_team_8;
extern IMPORTME dirty_int ALWAYS_EVALUATE;

//
// Function Imports
//

// AI & AI Teams
IMPORTME bool __cdecl IsAITeam(int);
IMPORTME void __cdecl AI_Attack(int);
IMPORTME void __cdecl AI_Attack(int unitHandle, int targetHandle);
IMPORTME void __cdecl AI_Attack(int, Vector3);
IMPORTME void __cdecl AI_Team_Load_AIP(character&, char*);
IMPORTME void __cdecl AI_Team_Load_AIP(int, char*);
IMPORTME void __cdecl DisableAllAITeams();
IMPORTME void __cdecl EnableAllAITeams();
IMPORTME void __cdecl SetIsAITeam(const int&, const bool&);

// Teams & Team Relations
IMPORTME bool __cdecl IsConfirmedAlly(int, int);
IMPORTME bool __cdecl IsConfirmedEnemy(int, int);
IMPORTME bool __cdecl IsConfirmedNeutral(int, int);
IMPORTME bool __cdecl IsUnconfirmedAlly(int, int);
IMPORTME bool __cdecl IsUnconfirmedEnemy(int, int);
IMPORTME bool __cdecl IsUnconfirmedNeutral(int, int);
IMPORTME bool __cdecl IsVisibleToTeam(int, int);
IMPORTME float __cdecl GetTeamCrew(int);
IMPORTME float __cdecl SetTeamCrew(int, float);
IMPORTME int __cdecl GetPerceivedTeam(int);
IMPORTME int __cdecl GetPercievedTeamOfFlag(int);
IMPORTME int __cdecl GetRealTeam(int);
IMPORTME int __cdecl GetRealTeamOfFlag(int);
IMPORTME void __cdecl DisableTeam(int);
IMPORTME void __cdecl EnableTeam(int);
IMPORTME void __cdecl SetPerceivedTeam(int, int);
IMPORTME void __cdecl SetRealTeam(int, int);
IMPORTME void __cdecl SetRelation(int, int, Team::TeamRelation);

// Attacking & Combat Commands
IMPORTME bool __cdecl InAttackMode(int unitHandle);
IMPORTME bool __cdecl UnderAttack(int, float);
IMPORTME int __cdecl GetAllyShipAttacks(int, int);
IMPORTME int __cdecl GetAllyStationAttacks(int, int);
IMPORTME Vector3 __cdecl GetAttackLocation(int, int);
IMPORTME void __cdecl AllowMultipleSpecialWeaponFire(int, bool);
IMPORTME void __cdecl Attack(int unitHandle, int targetHandle, int);
IMPORTME void __cdecl Attack(int, Vector3);
IMPORTME void __cdecl AttackMainEnemyBase(int, bool);
IMPORTME void __cdecl CommandAllShips(AiCommand, int, const char*, bool, bool);
IMPORTME void __cdecl SearchAndDestroy(int);
IMPORTME void __cdecl Special_Attack(int, const char*);
IMPORTME void __cdecl Special_Attack(int, int, const char*);
IMPORTME void __cdecl Special_Attack(int, Vector3, const char*);

// Building & Construction
IMPORTME int __cdecl BuildObject(char* odfName, int team, char* waypointLabel, int);
IMPORTME int __cdecl BuildObject(char*, int, int, float, float, float);
IMPORTME void __cdecl Build(int, char*);

// Ship Systems
IMPORTME bool __cdecl EnginesActive(int unitHandle);
IMPORTME bool __cdecl EnginesDestroyed(int unitHandle);
IMPORTME bool __cdecl EnginesDisabled(int unitHandle);
IMPORTME bool __cdecl LifeSupportActive(int unitHandle);
IMPORTME bool __cdecl LifeSupportDestroyed(int unitHandle);
IMPORTME bool __cdecl LifeSupportDisabled(int unitHandle);
IMPORTME bool __cdecl SensorsActive(int unitHandle);
IMPORTME bool __cdecl SensorsDestroyed(int unitHandle);
IMPORTME bool __cdecl SensorsDisabled(int unitHandle);
IMPORTME bool __cdecl ShieldGeneratorActive(int unitHandle);
IMPORTME bool __cdecl ShieldGeneratorDestroyed(int unitHandle);
IMPORTME bool __cdecl ShieldGeneratorDisabled(int unitHandle);
IMPORTME bool __cdecl WeaponsActive(int unitHandle);
IMPORTME bool __cdecl WeaponsDestroyed(int unitHandle);
IMPORTME bool __cdecl WeaponsDisabled(int unitHandle);
IMPORTME void __cdecl CraftCannotDie(int unitHandle, bool);
IMPORTME void __cdecl DestroyCritical(int unitHandle);
IMPORTME void __cdecl DestroyEngines(int unitHandle);
IMPORTME void __cdecl DestroyLifeSupport(int unitHandle);
IMPORTME void __cdecl DestroySensors(int unitHandle);
IMPORTME void __cdecl DestroyShieldGenerator(int unitHandle);
IMPORTME void __cdecl DestroyWeapons(int unitHandle);
IMPORTME void __cdecl DisableEngines(int, bool);
IMPORTME void __cdecl DisableLifeSupport(int unitHandle, bool);
IMPORTME void __cdecl DisableSensors(int unitHandle, bool);
IMPORTME void __cdecl DisableShieldGenerator(int unitHandle, bool);
IMPORTME void __cdecl DisableWeapons(int unitHandle, bool);

// Alerts
IMPORTME bool __cdecl IsGreenAlert(int unitHandle);
IMPORTME bool __cdecl IsRedAlert(int unitHandle);
IMPORTME bool __cdecl IsYellowAlert(int unitHandle);
IMPORTME void __cdecl SetGreenAlert(int unitHandle);
IMPORTME void __cdecl SetRedAlert(int unitHandle);
IMPORTME void __cdecl SetYellowAlert(int unitHandle);

// Wormholes & Transwarp
IMPORTME int __cdecl GetNearestTranswarpGate(int);
IMPORTME int __cdecl GetTranswarpExitWormhole(int);
IMPORTME void __cdecl EnableWormholeTravel(int, bool);
IMPORTME void __cdecl LinkWormHoles(int, int);
IMPORTME void __cdecl SetWormholeTeam(int, int);

// Navigation & Movement
IMPORTME float __cdecl GetImpulseSpeed(int);
IMPORTME float __cdecl GetWarpSpeed(int);
IMPORTME void __cdecl GetRepair(int);
IMPORTME void __cdecl Goto(int unitHandle, char* waypointLabel, int);
IMPORTME void __cdecl Goto(int, int, int);
IMPORTME void __cdecl Mine(int, int);
IMPORTME void __cdecl ObstacleAvoidence(bool enable);
IMPORTME void __cdecl Patrol(int, char*);
IMPORTME void __cdecl PointAt(int, char*);
IMPORTME void __cdecl PointAt(int, int);
IMPORTME void __cdecl ResetWarpSpeed(int);
IMPORTME void __cdecl Scout(int);
IMPORTME void __cdecl SetImpulseSpeed(int, float);
IMPORTME void __cdecl SetPathType(char*, PathType);
IMPORTME void __cdecl SetPosition(int unitHandle, char* waypointLabel);
IMPORTME void __cdecl SetWarpSpeed(int unitHandle, float _speed);
IMPORTME void __cdecl Stop(int, int);
IMPORTME void __cdecl StopAllShips(int, const char*, bool, bool);

// Object & Unit Finding
IMPORTME const Vector3& __cdecl GetLocation(char*, int);
IMPORTME const Vector3& __cdecl GetLocation(int unitHandle);
IMPORTME float __cdecl GetDistance(int& unitHandle, char* waypointLabel, int);
IMPORTME float __cdecl GetDistance(int&, int&);
IMPORTME int __cdecl CountUnits(int team, char* odfName);
IMPORTME int __cdecl CountUnitsInRectangle(char*, int, char*, int, int);
IMPORTME int __cdecl CountUnitsNearObject(int, float, int, char*);
IMPORTME int __cdecl CountUnitsNearPoint(char*, float, int, char*, int);
IMPORTME int __cdecl CountVisibleUnits(int, int, bool, char*);
IMPORTME int __cdecl CountVisibleUnitsNearObject(int, float, int, bool, char*);
IMPORTME int __cdecl CountVisibleUnitsNearPoint(int, char*, float, int, bool, char*, int);
IMPORTME int __cdecl GetNearestEnemy(int unitHandle, float range);
IMPORTME int __cdecl GetNearestObject(int);
IMPORTME int __cdecl GetNearestObjectNearMe(int, float, int, char*, int, bool);
IMPORTME int __cdecl GetNearestObjectNearPosition(const Vector3&, float, int, char*, int, bool, int);
IMPORTME int __cdecl GetNearestRepairFacility(int, int);
IMPORTME int __cdecl GetNearestShipyard(int, int, bool);
IMPORTME int __cdecl GetNearestStarbase(int unitHandle, int _team);
IMPORTME int __cdecl GetNearestVehicle(char*, int);
IMPORTME int __cdecl GetNearestVehicle(int);

// Effects
IMPORTME void __cdecl AddBillboardEffect(int, char*);
IMPORTME void __cdecl AddTransporterEffect(int);
IMPORTME void __cdecl EnableLight(int, bool);
IMPORTME void __cdecl HideObject(int, bool);
IMPORTME void __cdecl RemoveBillboardEffect(int);

// Titles, Subtitles & Screen Effects
IMPORTME int __cdecl ShowSubtitle(int, int, int, int, const char* message, bool);
IMPORTME int __cdecl ShowTitle(int, int, int, int, const char*, bool);
IMPORTME void __cdecl CenterCamera(char*, int);
IMPORTME void __cdecl FadeIn(float, float, float);
IMPORTME void __cdecl FadeOut(float, float, float);
IMPORTME void __cdecl FadeRemove();
IMPORTME void __cdecl RemoveSubtitle(int, bool);
IMPORTME void __cdecl RemoveTitle(int, bool);

// Cineractives / Camera
IMPORTME void __cdecl CineractiveCameraOffset(char*, float, bool);
IMPORTME void __cdecl CineractiveCameraOffset(float, float, float, bool);
IMPORTME void __cdecl CineractiveEnd();
IMPORTME void __cdecl CineractiveShot(char*, float, bool);
IMPORTME void __cdecl CineractiveShot(char*, float, char*, float);
IMPORTME void __cdecl CineractiveShot(char*, float, char*, int);
IMPORTME void __cdecl CineractiveShot(char*, float, int);
IMPORTME void __cdecl CineractiveShot(char*, int, bool);
IMPORTME void __cdecl CineractiveShot(char*, int, char*, float);
IMPORTME void __cdecl CineractiveShot(char*, int, char*, int);
IMPORTME void __cdecl CineractiveShot(char*, int, int);
IMPORTME void __cdecl CineractiveShot(int, bool);
IMPORTME void __cdecl CineractiveShot(int, char*, float);
IMPORTME void __cdecl CineractiveShot(int, char*, int);
IMPORTME void __cdecl CineractiveShot(int, int);
IMPORTME void __cdecl CineractiveShotTrackLeft(char*, int, char*, int, int);
IMPORTME void __cdecl CineractiveStart();
IMPORTME void __cdecl CineractiveTargetOffset(char*, float, bool);
IMPORTME void __cdecl CineractiveTargetOffset(float, float, float, bool);

// Bridge Scenes
IMPORTME void __cdecl PreLoadBridgeScene(BridgeDisplay::BridgeType);
IMPORTME void __cdecl SetBridgeSceneRace(BridgeDisplay::BridgeType);
IMPORTME void __cdecl ShowBridgeOnScreen(bool);
IMPORTME void __cdecl ShowBridgeScene(bool);

// Movies
IMPORTME bool __cdecl IsMoviePlaying();
IMPORTME void __cdecl PlayBridgeMovie(char*, int);
IMPORTME void __cdecl PlayCinematicMovie(char*, int);
IMPORTME void __cdecl StopMovie();

// Audio
IMPORTME bool __cdecl IsAudioMessageDone(int audioHandle);
IMPORTME int __cdecl AudioMessage(const char* filename);
IMPORTME void __cdecl StopAudioMessage(int audioHandle);

// Credits
IMPORTME void __cdecl EndCredits();
IMPORTME void __cdecl StartCredits();

// Groups
IMPORTME void __cdecl Add_Team_To_Group(int, group&);
IMPORTME void __cdecl add_unit_to_group(group&, character&);
IMPORTME void __cdecl remove_unit_from_group(group&, character&);

// Resources
IMPORTME float __cdecl AddCrew(int, float);
IMPORTME float __cdecl AddOfficers(int, float);
IMPORTME int __cdecl AddDilithium(int, int);
IMPORTME float __cdecl GetCrew(int);
IMPORTME float __cdecl GetOfficers(int);
IMPORTME int __cdecl GetDilithium(int);
IMPORTME float __cdecl GetDilithiumOnFreighter(int);
IMPORTME float __cdecl GetMaxCrew(int);
IMPORTME float __cdecl GetMaxOfficers(int);
IMPORTME int __cdecl GetMaxDilithium(int);
IMPORTME void __cdecl SetCrew(int, float);
IMPORTME float __cdecl SetOfficers(int, float);
IMPORTME int __cdecl SetDilithium(int team, int value);

// Special Flags
IMPORTME bool __cdecl IsRaceOfFlag(int, char*);
IMPORTME int __cdecl CreateSpecialFlag(int, char*);
IMPORTME int __cdecl GetLocationOfFlag(int);
IMPORTME void __cdecl RestrictSpecialFlag(int, SpecialFlag::Restriction);
IMPORTME void __cdecl RestrictSpecialFlag(int, SpecialFlag::Restriction, char*);
IMPORTME void __cdecl RestrictSpecialFlag(int, SpecialFlag::Restriction, int);
IMPORTME void __cdecl TransferFlag(int, int);

// Scripts, Rules & Events
IMPORTME bool __cdecl LoadScriptUtils(_iobuf*);
IMPORTME bool __cdecl PostLoadScriptUtils();
IMPORTME bool __cdecl SaveScriptUtils(_iobuf*);
IMPORTME int __cdecl FindGameEvent(const char*);
IMPORTME int __cdecl Load_Action_Scripts(char*);
IMPORTME int __cdecl Load_Rules(char*);
IMPORTME void __cdecl Trash_Action_Scripts(int);
IMPORTME void __cdecl Trash_Rules(int);
IMPORTME void __cdecl TriggerGameEvent(int, int);

// Shields, Special Energy & Cloaking
IMPORTME bool __cdecl OutOfSpecialAttackMode(int);
IMPORTME float __cdecl GetRealShieldPercent(int);
IMPORTME float __cdecl GetShieldPercent(int);
IMPORTME float __cdecl GetSpecialEnergy(int);
IMPORTME void __cdecl Cloak(int);
IMPORTME void __cdecl Decloak(int);
IMPORTME void __cdecl ImmediateCloak(int);
IMPORTME void __cdecl SetMaxShields(int, float);
IMPORTME void __cdecl SetShieldPercent(int unitHandle, float fraction);
IMPORTME void __cdecl SetSpecialEnergy(int, float);

// Object State & Identity
IMPORTME bool __cdecl DoesNotExist(int);
IMPORTME bool __cdecl Exists(int);
IMPORTME bool __cdecl InQueue(int unitHandle);
IMPORTME bool __cdecl InStopMode(int);
IMPORTME bool __cdecl IsAlive(int);
IMPORTME bool __cdecl IsCompromised(int unitHandle, int team);
IMPORTME bool __cdecl IsDerelict(int);
IMPORTME bool __cdecl IsEnabled(int);
IMPORTME bool __cdecl IsExploding(int);
IMPORTME bool __cdecl IsOdf(int, char*);
IMPORTME bool __cdecl IsRace(int, const char*);
IMPORTME bool __cdecl IsThereARomulanSpyOnShip(int);
IMPORTME bool __cdecl IsValid(int);
IMPORTME int __cdecl GetHandle(char*);

// Object Lifecycle & Modification
IMPORTME bool __cdecl RecruitSpecialForces(char*, int, int&);
IMPORTME int __cdecl ReplaceObject(int, char*);
IMPORTME void __cdecl ClearRestrictions(int);
IMPORTME void __cdecl RemoveAllCraft(bool, int);
IMPORTME void __cdecl RemoveAllObjects();
IMPORTME void __cdecl RemoveObject(int);
IMPORTME void __cdecl SetSpecialForcesFlag(int unitHandle, bool flag);
IMPORTME void __cdecl SetSpecialWeaponAttackInterval(int, float);

// Mission Outcome
IMPORTME void __cdecl FailMission(float, char*);
IMPORTME void __cdecl SucceedMission(float, char*);

// Map, Minimap & Objectives
IMPORTME void __cdecl GridVisible(bool);
IMPORTME void __cdecl Log_Message(char*);
IMPORTME void __cdecl MinimapMessage(char*, int, float, int);
IMPORTME void __cdecl MinimapMessage(int unitHandle, int, float);
IMPORTME void __cdecl ObjectivesDisplay_Set_Text_From_File(char* filename);
IMPORTME void __cdecl ObjectivesDisplay_Set_Visibility(bool visible);
IMPORTME void __cdecl Starfield_Load_Background_Geometry(char*);

// Simulation Control
IMPORTME float __cdecl GetTime();
IMPORTME void __cdecl PauseSimulation();
IMPORTME void __cdecl UnpauseSimulation();

// Other / General Object Functions
IMPORTME void __cdecl SetRace(int, const char*);


// Script file serialization helpers
IMPORTME bool __cdecl in(_iobuf* io, char* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, unsigned char* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, short* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, unsigned short* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, int* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, long* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, unsigned long* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, float* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, double* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, EULER* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, Matrix34* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, Vector2* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, Vector3* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, hot_float* ref);
IMPORTME bool __cdecl in(_iobuf* io, hot_int* ref);
IMPORTME bool __cdecl in(_iobuf* io, timer_int* ref);
IMPORTME bool __cdecl in(_iobuf* io, void* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, __int64* ref, unsigned int size);
IMPORTME bool __cdecl in(_iobuf* io, bool* ref, unsigned int size);

IMPORTME bool __cdecl out(_iobuf* io, char* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, unsigned char* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, short* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, unsigned short* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, int* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, long* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, unsigned long* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, float* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, double* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, EULER* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, Matrix34* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, Vector2* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, Vector3* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, hot_float* ref, char* name);
IMPORTME bool __cdecl out(_iobuf* io, hot_int* ref, char* name);
IMPORTME bool __cdecl out(_iobuf* io, timer_int* ref, char* name);
IMPORTME bool __cdecl out(_iobuf* io, void* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, __int64* ref, unsigned int size, char* name);
IMPORTME bool __cdecl out(_iobuf* io, bool* ref, unsigned int size, char* name);
