// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <utility>
#include <limits>

using std::string;
using std::vector;
using std::pair;

#include <unordered_map>
using std::unordered_map;

#include <map>
using std::map;

#include <algorithm>

using namespace std;

// Type for town IDs
using TownID = std::string;

// Return value for cases where required town was not found
TownID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

// Type for a coordinate (x, y)
using Coord = std::pair<int, int>;

// Return value for cases where coordinates were not found
Coord const NO_COORD{NO_VALUE, NO_VALUE};

// Type for distance
using Dist = int;

// Return value for cases where distance is unknown
Dist const NO_DIST = NO_VALUE;


struct NodeRoute
{
    TownID id_now = NO_ID;
    int distance = INFINITY;
    NodeRoute* from = nullptr;
};


struct LessDistance
{
    bool operator()(NodeRoute* lhs, NodeRoute* rhs) const
    {
        return lhs->distance > rhs->distance;
    }
};


struct Routs
{
    unordered_map<TownID, Cost> routs_map;
};

typedef std::priority_queue<NodeRoute*, std::vector<NodeRoute*>, LessDistance> pq_type;
typedef pair<TownID, Cost> friend_pair;
typedef unordered_map<TownID, Friend*> unordered_map_rout;

struct Town
{
    TownID town_id;
    std::string name;
    int x;
    int y;
    int tax;
    Town* master_pointer;
    vector<TownID> vassalsID_vec;

};

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    unsigned int size();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear();

    // Estimate of performance:
    // Short rationale for estimate:
    std::string get_name(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_coordinates(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int get_tax(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> get_vassals(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> all_towns();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_town(TownID id, std::string const& name, int x, int y, int tax);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_town_name(TownID id, std::string const& newname);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> find_towns(std::string const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    TownID min_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID max_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID nth_distance(unsigned int n);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> taxer_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_roads();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_town(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_distance_increasing_from(int x, int y);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance:
    // Short rationale for estimate:
    Dist trim_road_network();




    // #################################################################

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: This function includes a for loop
    // in which it calls another function with complexity of O(n).
    int vassals_tax(TownID id);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: This function only includes an addition a constant
    // to an output by calling the above function.
    int total_tax(TownID id);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: It includes a for loop on the vassals vector of a town and
    // then recursively calls itself and push_back the ids to a vector.
    pair<int, vector<TownID>> path_ids_func(TownID id);


private:
    // Add stuff needed for your class implementation here


    unordered_map<TownID, Town*>  town_main_map;
    multimap<string, TownID> map_alpha_sorted;
    multimap<int, TownID> map_dist_sorted;
    vector<Town*> town_ptr_vec;
    unordered_map_rout rout_unordered_map;

};

#endif // DATASTRUCTURES_HH
