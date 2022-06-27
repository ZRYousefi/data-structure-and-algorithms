// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>


using namespace std;
struct TownData
{
    std::string name;
    int x;
    int y;
};

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: complexity of the size function is constant.
    unsigned int size();

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    void clear();

    // Estimate of performance: O(n)
    // Short rationale for estimate: It includes a for loop with a constant complexity, therefore the final complexity of this function will be linear.
    std::vector<TownData*> all_towns();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Complexity here is constant but if the number of input town get more,
                                  // reallocation may happen which its complexity is up to linear.
    TownData* add_town(std::string const& name, int x, int y);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: I am applying merge sort therefore the complexity will be nlogn because dataset is repeatedly divided into half
                                     // and each half is processed again independently.
    std::vector<TownData*> towns_alphabetically();

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: Similar to the above function.
    std::vector<TownData*> towns_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: There is a for loop in this function.
    TownData* find_town(std::string const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: In case the input vector is not sorted it includes a simple for loop to find the minimum distance town.
    TownData* min_distance();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Similar to the above procedure.
    TownData* max_distance();

    // Estimate of performance: O(n^2) in worst case
    // Short rationale for estimate: For this function I used quick select which does not need to sort the vector to find the nth element.
                                     // Its average performance is O(n).
    TownData* nth_distance(unsigned int n);

    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: It has a for loop and the erase function which is linear for the number of elements that needs to be erased.
                                     // Here we want to remove one twn, therefore, the final complexity will be linear.
    void remove_town(std::string const& town_name);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: I am applying merge sort here.
    std::vector<TownData*> towns_distance_increasing_from(int x, int y);

private:
    // Add stuff needed for your class implementation here
    vector<TownData> townsVec;
    int sorted_alph;
    int sorted_dist;
    vector<TownData*> alphSortedTowns;
    vector<TownData*> distSortedTowns;
    vector<TownData*> townDist;

};

#endif // DATASTRUCTURES_HH
