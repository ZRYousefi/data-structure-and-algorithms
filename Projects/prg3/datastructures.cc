// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}



vector<TownID> masters_id_func(vector<TownID>& masters_ids, Town* pointer)
{
    if (pointer->master_pointer != nullptr)
    {
        masters_ids.push_back(pointer->master_pointer->town_id);
        masters_id_func(masters_ids, pointer->master_pointer);
    }
    return masters_ids;

}




Datastructures::Datastructures()
{
 // Replace with actual implementation
}

Datastructures::~Datastructures()
{
 // Replace with actual implementation
}

unsigned int Datastructures::size()
{
    return town_main_map.size();
}

void Datastructures::clear()
{

    for (Town* town : town_ptr_vec)
    {
        delete town;
    }
    town_main_map.clear();
    map_alpha_sorted.clear();
    map_dist_sorted.clear();
    town_ptr_vec.clear();
    for(unordered_map_rout::iterator it=rout_unordered_map.begin(); it!=rout_unordered_map.end(); it++)
    {
        delete(it->second);
    }
    rout_unordered_map.clear();

//    town_main_map.clear();
//    map_alpha_sorted.clear();
//    map_dist_sorted.clear();
}

std::string Datastructures::get_name(TownID id)
{
    if (town_main_map.find(id) != town_main_map.end())
    {
        string name = town_main_map.at(id)->name;
        return name;
    }
    return NO_NAME;
}

Coord Datastructures::get_coordinates(TownID id)
{
    if (town_main_map.find(id) != town_main_map.end())
    {
        int x = town_main_map.at(id)->x;
        int y = town_main_map.at(id)->y;
        return {x, y};
    }
    return {NO_VALUE, NO_VALUE};
}

int Datastructures::get_tax(TownID id)
{
    if (town_main_map.find(id) != town_main_map.end())
    {
        int tax = town_main_map.at(id)->tax;
        return tax;
    }
    return NO_VALUE;
}

std::vector<TownID> Datastructures::get_vassals(TownID id)
{
    if (town_main_map.find(id) != town_main_map.end())
    {
        Town* tempTown = town_main_map[id];
        sort(tempTown->vassalsID_vec.begin(), tempTown->vassalsID_vec.end());
        return (tempTown)->vassalsID_vec;
    }
    return {NO_ID};
}

std::vector<TownID> Datastructures::all_towns()
{
    vector<TownID> towns_id;
    for (unordered_map<TownID, Town*>::iterator it = town_main_map.begin(); it != town_main_map.end(); ++it){
        towns_id.push_back(it->first);
    }
    return {towns_id};
}

bool Datastructures::add_town(TownID id, const std::string& name, int x, int y, int tax)
{
    Town* tempTown = new Town;
    tempTown->town_id = id;
    tempTown->name = name;
    tempTown->x = x;
    tempTown->y = y;
    tempTown->tax = tax;
    tempTown->master_pointer = nullptr;
    tempTown->vassalsID_vec = {};
    if (town_main_map.find(id) == town_main_map.end())
    {
        town_main_map[id] = tempTown;
        map_alpha_sorted.insert({name,id});
        map_dist_sorted.insert({abs(x)+abs(y),id});
        town_ptr_vec.push_back(tempTown);
        return true;
    }
    return false;
}

bool Datastructures::change_town_name(TownID id, const std::string& newname)
{
    if (town_main_map.find(id) != town_main_map.end())
    {
        unordered_map<TownID, Town*>::iterator i = town_main_map.find(id);
        Town* changing_name = i->second;
        string old_name = changing_name->name;
        changing_name->name = newname;
        pair <multimap<string, TownID>::iterator, multimap<string, TownID>::iterator> ret = map_alpha_sorted.equal_range(old_name);
        for (std::multimap<string, TownID>::iterator it = ret.first; it != ret.second; ++it)
        {
            if (it->second == id) {
                map_alpha_sorted.erase(it);
                map_alpha_sorted.insert({newname, id});
                break;
            }
        }
    }
    return false;
}

bool Datastructures::remove_town(TownID id)
{
    return false; // Replace with actual implementation
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    vector<TownID> towns_id;
    for (multimap<string, TownID>::iterator it = map_alpha_sorted.begin(); it != map_alpha_sorted.end(); ++it){
        towns_id.push_back(it->second);
    }
    return towns_id;
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    vector<TownID> towns_id;
    for (multimap<int, TownID>::iterator it = map_dist_sorted.begin(); it != map_dist_sorted.end(); ++it){
        towns_id.push_back(it->second);
    }
    return towns_id;
}

std::vector<TownID> Datastructures::find_towns(std::string const& name)
{
    vector<TownID> towns_id;
    pair <multimap<string, TownID>::iterator, multimap<string, TownID>::iterator> name_range_iter = map_alpha_sorted.equal_range(name);
    for (multimap<string,TownID>::iterator it = name_range_iter.first; it != name_range_iter.second; ++it)
        towns_id.push_back(it->second);
    sort(towns_id.begin(), towns_id.end());
    return towns_id;
}

TownID Datastructures::min_distance()
{
    if (map_dist_sorted.size() > 0) {
        multimap<int, TownID>::iterator it = map_dist_sorted.begin();
        return (it->second);
    }
    return NO_ID;
}

TownID Datastructures::max_distance()
{
    if (map_dist_sorted.size() > 0) {
        multimap<int, TownID>::reverse_iterator rit = map_dist_sorted.rbegin();
        return (rit->second);
    }
    return NO_ID;
}

TownID Datastructures::nth_distance(unsigned int n)
{
    int cnt = 0;
    for (map<int, TownID>::iterator it = map_dist_sorted.begin(); it != map_dist_sorted.end(); ++it){
        cnt+=1;
        if (cnt == n ){
            return (it->second);
        }
    }
    return NO_ID;
}

std::vector<TownID> Datastructures::towns_distance_increasing_from(int x, int y)
{
    multimap<int, TownID> towns_dist_xy;
    for (unordered_map<TownID, Town*>::iterator it = town_main_map.begin(); it != town_main_map.end(); ++it){
        towns_dist_xy.insert({abs(it->second->x - x) +  abs(it->second->y - y),it->first});
    }

    vector<TownID> towns_id_dist_xy;
    for (multimap<int, TownID>::iterator iterator = towns_dist_xy.begin(); iterator != towns_dist_xy.end(); ++iterator){
        towns_id_dist_xy.push_back(iterator->second);
    }
    return towns_id_dist_xy;
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    if (town_main_map.find(vassalid) != town_main_map.end() && town_main_map.find(masterid) != town_main_map.end())
    {
        unordered_map<TownID, Town*>::iterator vassalit = town_main_map.find(vassalid);
        unordered_map<TownID, Town*>::iterator masterit = town_main_map.find(masterid);
        TownID vassalID = vassalit->first;
        Town* masterPTR = masterit->second;

        if (masterPTR->master_pointer != vassalit->second && vassalit->second->master_pointer == nullptr)
        {
            vassalit->second->master_pointer = masterPTR;
            (masterit->second->vassalsID_vec).push_back(vassalID);
            return true;
        }
    }
    return false;
}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    if (town_main_map.find(id) == town_main_map.end() || town_main_map.at(id)->master_pointer == nullptr) {
        return {};
    }
    else {
        vector<TownID> masters_id = {id};
        masters_id = masters_id_func(masters_id, town_main_map.at(id));
        return masters_id;
    }
}

std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    return {}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::get_roads_from(TownID id)
{
    return {NO_ID}; // Replace with actual implementation
}

bool Datastructures::add_road(TownID town1, TownID town2)
{
    return false; // Replace with actual implementation
}

bool Datastructures::remove_road(TownID town1, TownID town2)
{
    return false; // Replace with actual implementation
}

void Datastructures::clear_roads()
{
 // Replace with actual implementation
}

std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{
    return {NO_ID}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    if (town_main_map.find(id) != town_main_map.end()) {
        vector<TownID> path_vec ={};
        path_vec = path_ids_func(id).second;

        std::reverse(path_vec.begin(), path_vec.end());
        return path_vec;
    }
    else return {};
}

int Datastructures::total_net_tax(TownID id)
{
    if (town_main_map.find(id) != town_main_map.end()) {
        int net_tax = 0;
        int tmp_tax = town_main_map.at(id)->tax + vassals_tax(id);
        if(town_main_map.at(id)->master_pointer == nullptr) {
            net_tax = tmp_tax;
        }
        else (net_tax = tmp_tax - (tmp_tax/10) );
        return   net_tax;
        }
    return NO_VALUE;
}

std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{
    return {NO_ID}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::shortest_route(TownID fromid, TownID toid)
{
    return {NO_ID}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::road_cycle_route(TownID startid)
{
    return {NO_ID}; // Replace with actual implementation
}

Dist Datastructures::trim_road_network()
{
    return NO_DIST; // Replace with actual implementation
}




//    #############################################################



int Datastructures::vassals_tax(TownID id)
{
    int v_tax = 0;
    unordered_map<TownID, Town*>::iterator it = town_main_map.find(id);
    vector<TownID> vassalsID = it->second->vassalsID_vec;
    for (vector<TownID>::iterator i = vassalsID.begin(); i != vassalsID.end(); ++i){
            v_tax = v_tax + (total_tax(*i)/10);
        }
    return v_tax;
}


int Datastructures::total_tax(TownID id)
{
        int totaltax = 0;
        totaltax = town_main_map.at(id)->tax + vassals_tax(id);
        return totaltax;
}



pair<int, vector<TownID>> Datastructures::path_ids_func(TownID id)
{
    unordered_map<TownID, Town*>::iterator it = town_main_map.find(id);
    int h = 0;
    vector<TownID> path_vec;
    vector<TownID> vassalsID = (it->second)->vassalsID_vec;
    if (vassalsID.empty()) {
        path_vec.push_back(id);
    }
    else {
        for (vector<TownID>::iterator i = vassalsID.begin(); i != vassalsID.end(); ++i){
            if (h < path_ids_func(*i).first) {
                auto temp = path_ids_func(*i).second;
                path_vec = temp;
                h = path_ids_func(*i).first;
            }
        }
        path_vec.push_back(id);
    }
        h+=1;

        return {h, path_vec};
}
