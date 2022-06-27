// Datastructures.cc

#include "datastructures.hh"

#include <random>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator


template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

//---------------My sort functions -------------------//


// ------------------------- Merge sort ----------------- //
void merge(vector<TownData*> &townList, int l, int m, int r, int sort_type, int xRef, int yRef)
{
    int  i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    vector<TownData*> L(townList.begin() + l, townList.begin() + n1 + l );
    vector<TownData*> R(townList.begin() + m + 1, townList.begin() + m + n2 + 1);

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (sort_type == 0) {
            if ( (*L[i]).name <= (*R[j]).name )
            {
                townList[k] = L[i];
                i++;
            }
            else
            {
                townList[k] = R[j];
                j++;
            }
            k++;
        } else if (sort_type == 1) {
            if (abs((*L[i]).x)+abs((*L[i]).y) <=  abs((*R[j]).x)+abs((*R[j]).y))
            {
                townList[k] = L[i];
                i++;
            }
            else
            {
                townList[k] = R[j];
                j++;
            }
            k++;
        } else
        {
            if (abs((*L[i]).x - xRef)+abs((*L[i]).y - yRef) <=  abs((*R[j]).x - xRef)+abs((*R[j]).y - yRef))
            {
                townList[k] = L[i];
                i++;
            }
            else
            {
                townList[k] = R[j];
                j++;
            }
            k++;

        }
    }

    while (i < n1)
    {
        townList[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        townList[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<TownData*> &townList, int l, int r,int sort_type, int xRef, int yRef)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(townList, l, m, sort_type, xRef, yRef);
        mergeSort(townList, m+1, r, sort_type, xRef, yRef);
        merge(townList, l, m, r, sort_type, xRef, yRef);
    }
}
// -------------------------------------------------------------------- //

// --------------------------- Quick Select -------------------------- //


int partition(vector<TownData*> &townDist, int l, int r)
{
    int pivot = abs((*townDist[r]).x)+abs((*townDist[r]).y);

    while ( l < r )
    {
        while ( abs((*townDist[l]).x)+abs((*townDist[l]).y) < pivot )
            l++;

        while ( abs((*townDist[r]).x)+abs((*townDist[r]).y) > pivot )
            r--;

        if ( abs((*townDist[l]).x)+abs((*townDist[l]).y) == abs((*townDist[r]).x)+abs((*townDist[r]).y) )
            l++;
        else if ( l < r ) {
            TownData* tmp = &(*townDist[l]);
            townDist[l] = townDist[r];
            townDist[r] = tmp;
        }
    }

    return r;
}

TownData* quickSelect(vector<TownData*> &townDist, int l, int r, int n)
{
    if ( l == r ) return &(*townDist[l]);
    int split = partition(townDist, l, r);
    int length = split - l + 1;
    if ( length == n ) return &(*townDist[split]);
    else if ( n < length ) return quickSelect(townDist, l, split - 1, n);
    else return quickSelect(townDist, split + 1, r, n - length);
}


// ----------------------------------------------------------------- //


Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{

}

unsigned int Datastructures::size()
{
    return townsVec.size();
}

void Datastructures::clear()
{
    townsVec.clear();
    sorted_alph = 0;
    sorted_dist = 0;
}

std::vector<TownData*> Datastructures::all_towns()
{
    vector<TownData*> town_ptr;
    for (auto iter= townsVec.begin(); iter != townsVec.end(); ++iter)
        town_ptr.push_back(&(*iter));
    return {town_ptr};

}

TownData* Datastructures::add_town(const std::string& name, int x, int y)
{
//    sorted_alph = 0;
//    sorted_dist = 0;
    TownData town;
    TownData* out;

    town.name = name;
    town.x = x;
    town.y = y;

    townsVec.push_back(town);

    out = &townsVec.back();
    return out;


}

std::vector<TownData*> Datastructures::towns_alphabetically()
{
    if (sorted_alph == 1) {
        return alphSortedTowns;
    }
    else {
    int sort_type = 0;
    vector<TownData*> tempTownList;
    for (auto iter = townsVec.begin(); iter != townsVec.end(); ++iter)
        tempTownList.push_back(&(*iter));
    mergeSort(tempTownList, 0, townsVec.size() - 1, sort_type, 0, 0);
    sorted_alph= 1;
    alphSortedTowns = tempTownList;
    return alphSortedTowns;
    }
}

std::vector<TownData*> Datastructures::towns_distance_increasing()
{
    if (sorted_dist == 1) {
        return distSortedTowns;
    }
    else {
    int sort_type = 1;
    vector<TownData*> tempTownList;
    for (auto iter = townsVec.begin(); iter != townsVec.end(); ++iter)
        tempTownList.push_back(&(*iter));
    mergeSort(tempTownList, 0, townsVec.size() - 1, sort_type, 0, 0);
    sorted_dist= 1;
    distSortedTowns = tempTownList;
    return distSortedTowns;
    }
}

TownData* Datastructures::find_town(std::string const& name)
{
    for (auto iter = townsVec.begin(); iter != townsVec.end(); ++iter)
        if ((*iter).name == name){
            return &(*iter);
        }
//    TownData* out;
//    for(int ind=0; ind!=townsVec.size(); ++ind){
//        if (townsVec[ind].name == name) {
//            out = &townsVec[ind];
//            return out;
//        }
//    }
    return nullptr;
}

TownData* Datastructures::min_distance()
{
    if (sorted_dist == 1) {
        return *(distSortedTowns.begin());
    }
    else {
        vector<TownData>::iterator min_iter;
        min_iter = townsVec.begin();
        for (auto iter = townsVec.begin(); iter != townsVec.end(); ++iter)
            if (abs((*iter).x)+abs((*iter).y) < abs((*min_iter).x)+abs((*min_iter).y)) {
                min_iter = iter;
            }
        return &(*min_iter);
    }
}

TownData* Datastructures::max_distance()
{
    if (sorted_dist == 1) {
        return distSortedTowns.back();
    }
    else {
        vector<TownData>::iterator max_iter;
        max_iter = townsVec.begin();
        for (auto iter = townsVec.begin(); iter != townsVec.end(); ++iter)
            if (abs((*iter).x)+abs((*iter).y) > abs((*max_iter).x)+abs((*max_iter).y)) {
                max_iter = iter;
            }
        return &(*max_iter);
    }
}

TownData* Datastructures::nth_distance(unsigned int n)
{
    if (n==0 || n>townsVec.size()){
        return nullptr;
    }
    else {
        vector<TownData*> tempTownList;
        for (auto iter = townsVec.begin(); iter != townsVec.end(); ++iter)
            tempTownList.push_back(&(*iter));
        return quickSelect(tempTownList, 0, townsVec.size() - 1, n);
    }

}

void Datastructures::remove_town(const std::string& town_name)
{
    for (auto iter = townsVec.begin(); iter != townsVec.end(); ++iter)
        if (iter->name == town_name){
            townsVec.erase(iter);
            return;
        }

}

std::vector<TownData*> Datastructures::towns_distance_increasing_from(int x, int y)
{
    int sort_type = 2;
    vector<TownData*> tempTownList;
    for (auto iter = townsVec.begin(); iter != townsVec.end(); ++iter)
        tempTownList.push_back(&(*iter));
    mergeSort(tempTownList, 0, townsVec.size() - 1, sort_type, x, y);
    sorted_dist= 1;
    distSortedTowns = tempTownList;
    return distSortedTowns;
}
