#include<iostream>
#include "Ordered_list.h"
#include"Random.h"
#include"Timer.h"
#include"Sortable_list.h"
#include<string.h>
#include <climits>
using namespace std;

void print_out(std::string msg, const double& time, const int& comparisons, const int& searches);

int chooseVersion();
Error_code sequential_search(const List<Record>& the_list, const Key& target, int& position);
Error_code recursive_binary_1(const Ordered_list& the_list, const Key& target,
    int bottom, int top, int& position);
Error_code run_recursive_binary_1(const Ordered_list& the_list,
    const Key& target, int& position);
Error_code binary_search_1(const Ordered_list& the_list,
    const Key& target, int& position);
Error_code recursive_binary_2(const Ordered_list& the_list, const Key& target,
    int bottom, int top, int& position);
Error_code run_recursive_binary_2(const Ordered_list& the_list,
    const Key& target, int& position);
Error_code binary_search_2(const Ordered_list& the_list,
    const Key& target, int& position);
void test_search(int searches, List<Record>& the_list);
void test_search_2(int searches, Ordered_list& the_list);
int main() {
    int MAX_SIZE;
    Key* key;
    int b;
    Random number;
    int option = chooseVersion();
    cout << "Insert the SIZE: ";
    cin >> MAX_SIZE; 
    switch (option)
    {
    case 1:
    {    
        Ordered_list li;
        for (int i = 0; i < MAX_SIZE; i++) {
            key = new Key(2 * i + 1 );
            li.insert(i,*key);
            delete key;
        }
        // Key::assignments-=MAX_SIZE;
        cout << "Insert searches: ";
        cin >> b;
        test_search(b, li);
        break;
    }
    case 2:
    {   
        Ordered_list li;
         for (int i = 0; i < MAX_SIZE; i++) {
            key = new Key(2 * i + 1 );
            li.insert(i,*key);
            delete key;
        }
        cout << "Insert searches: ";
        cin >> b;
        test_search_2(b, li);
        break;
    }
    case 3:
    {
        Sortable_list<Record> sort_li;
        Timer clock;
        for (int i = 0; i < MAX_SIZE; i++) {
            int a = number.random_integer(0,MAX_SIZE*2);
            key = new Key(a);
            sort_li.insert(i,*key);
            delete key;
        }
        Key::assignments = 0; 
        printList("\nBefore sort",sort_li);
        sort_li.insertion_sort();
        printList("\nAfter sort",sort_li);
        cout <<"\n\nTime: "<<clock.elapsed_time();
        cout <<"\nKey::assignments: "<<Key::assignments;
        cout <<"\nKey::comparisons: "<<Key::comparisons;
        break;
    }
    case 4:
    {
         Sortable_list<Record> sort_li;
        Timer clock;
        for (int i = 0; i < MAX_SIZE; i++) {
            int a = number.random_integer(0,MAX_SIZE*2);
            key = new Key(a);
            sort_li.insert(i,*key);
            delete key;
        }
        Key::assignments = 0;
        printList("\nBefore sort",sort_li);
        sort_li.quick_sort();
        printList("\nAfter sort",sort_li);
        cout <<"\n\nTime: "<<clock.elapsed_time();
        cout <<"\nKey::assignments: "<<Key::assignments;
        cout <<"\nKey::comparisons: "<<Key::comparisons;
        break;
    }
    default:
        break;
    }
}

Error_code sequential_search(const List<Record>& the_list, const Key& target, int& position) {
    int s = the_list.size();
    for (position = 0; position < s; position++) {
        Key data;
        the_list.retrieve(position, data);
        if (data == target) return success;
    }
    return not_present;
}

void test_search(int searches, List<Record>& the_list)
/*

Pre:  None.
Post: The number of key comparisons and CPU time for a
      sequential searching function have been calculated.
Uses: Methods of the classes List, Random, and Timer,
      together with an output function print_out
*/
{
    int list_size = the_list.size();
    if (searches <= 0 || list_size < 0) {
        cout << " Exiting test: " << endl
            << " The number of searches must be positive." << endl
            << " The number of list entries must exceed 0." << endl;
        return;
    }
    int i, target, found_at;
    Key::comparisons = 0;
    Random number;
    Timer clock;
    cout << "sequential_search: " << endl << "_ _ _ _ _ _ _ _ _ _ _ " << endl;
    for (i = 0; i < searches; i++) {
        target = 2 * number.random_integer(0, list_size - 1) + 1;
        if (sequential_search(the_list, target, found_at) == not_present)
            cout << "Error: Failed to find expected target " << target << endl;
    }
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        target = 2 * number.random_integer(0, list_size);
        if (sequential_search(the_list, target, found_at) == success)
            cout << "Error: Found unexpected target " << target
            << " at " << found_at << endl;
    }
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
}

void test_search_2(int searches, Ordered_list& the_list)
/*

Pre:  None.
Post: The number of key comparisons and CPU time for a
      sequential searching function have been calculated.
Uses: Methods of the classes List, Random, and Timer,
      together with an output function print_out
*/
{
    int list_size = the_list.size();
    if (searches <= 0 || list_size < 0) {
        cout << " Exiting test: " << endl
            << " The number of searches must be positive." << endl
            << " The number of list entries must exceed 0." << endl;
        return;
    }
    
    int i , found_at;
    Key::comparisons = 0;
    Random number;
    Timer clock;
    int odd_target[1000];
    //int *odd_target = new int(searches);
    
    for (i = 0; i < searches; i++) {
        odd_target[i] = 2 * number.random_integer(0, list_size - 1) + 1;
    }
    int even_target[1000];
    //int *even_target = new int(searches);
    for (i = 0; i < searches; i++) {
        even_target[i] = 2 * number.random_integer(0, list_size);
    }
    cout << "sequential_search: " << endl << "_ _ _ _ _ _ _ _ _ _ _ " << endl;
    for (i = 0; i < searches; i++) {
        if (sequential_search(the_list,odd_target[i], found_at) == not_present)
            cout << "Error: Failed to find expected target " << odd_target[i] << endl;
    }
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);
     
    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        if (sequential_search(the_list, even_target[i], found_at) == success)
            cout << "Error: Found unexpected target " << even_target[i]
            << " at " << found_at << endl;
    }
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
    
    cout << "run_recursive_binary_1: " << endl << "_ _ _ _ _ _ _ _ _ _ _ " << endl;
    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {  
          
        if (run_recursive_binary_1(the_list, odd_target[i], found_at) == not_present)
            cout << "Error: Failed to find expected target " << odd_target[i] << endl;
    }
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {   
        if (run_recursive_binary_1(the_list, even_target[i], found_at) == success)
            cout << "Error: Found unexpected target " << even_target[i]
            << " at " << found_at << endl;
    }
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);

    cout << "run_recursive_binary_2: " << endl << "_ _ _ _ _ _ _ _ _ _ _ " << endl;
    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        if (run_recursive_binary_2(the_list, odd_target[i], found_at) == not_present)
            cout << "Error: Failed to find expected target " << odd_target[i] << endl;
    }
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        if (run_recursive_binary_2(the_list, even_target[i], found_at) == success)
            cout << "Error: Found unexpected target " << even_target[i]
            << " at " << found_at << endl;
    }
   
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);

    cout << "binary_search_1: " << endl << "_ _ _ _ _ _ _ _ _ _ _ " << endl;
    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        if (binary_search_1(the_list, odd_target[i], found_at) == not_present)
            cout << "Error: Failed to find expected target " << odd_target[i] << endl;
    }
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        if (binary_search_1(the_list, even_target[i], found_at) == success)
            cout << "Error: Found unexpected target " << even_target[i]
            << " at " << found_at << endl;
    }
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);

    cout << "binary_search_2: " << endl << "_ _ _ _ _ _ _ _ _ _ _ " << endl;
    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        if (binary_search_2(the_list, odd_target[i], found_at) == not_present)
            cout << "Error: Failed to find expected target " <<  odd_target[i] << endl;
    }
    print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);

    Key::comparisons = 0;
    clock.reset();
    for (i = 0; i < searches; i++) {
        if (binary_search_2(the_list, even_target[i], found_at) == success)
            cout << "Error: Found unexpected target " << even_target[i]
            << " at " << found_at << endl;
    }
    print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons, searches);
    
}


Error_code recursive_binary_1(const Ordered_list& the_list, const Key& target,
    int bottom, int top, int& position)
    /*
    Pre:  The indices bottom to top define the
          range in the list to search for the target.
    Post: If a Record in the range of locations
          from bottom to top in the_list has key equal
          to target, then position locates
          one such entry and a code of success is returned.
          Otherwise, the Error_code of not_present is returned
          and position becomes undefined.
    Uses: recursive_binary_1 and methods of the classes List and Record.
    */
{
    Record data;
    if (bottom < top) {              // List has more than one entry.
        int mid = (bottom + top) / 2;
        the_list.retrieve(mid, data);
        if (data < target)  // Reduce to top half of list.
            return recursive_binary_1(the_list, target, mid + 1, top, position);
        else                          // Reduce to bottom half of list.
            return recursive_binary_1(the_list, target, bottom, mid, position);
    }
    else if (top < bottom)
        return not_present;           // List is empty.
    else {                           // List has exactly one entry.
        position = bottom;
        the_list.retrieve(bottom, data);
        if (data == target) return success;
        else return not_present;
    }
}

Error_code run_recursive_binary_1(const Ordered_list& the_list,
    const Key& target, int& position)
{   
    return recursive_binary_1(the_list, target, 0, the_list.size() - 1, position);
}

Error_code binary_search_1(const Ordered_list& the_list,
    const Key& target, int& position)
    /*
    Post: If a Record in the_list  has Key equal to target, then position locates
          one such entry and a code of success is returned.
          Otherwise, not_present is returned and position is undefined.
    Uses: Methods for classes List and Record.
    */
{   
    Record data;
    int bottom = 0, top = the_list.size() - 1;

    while (bottom < top) {
        int mid = (bottom + top) / 2;
        the_list.retrieve(mid, data);
        if (data < target)
            bottom = mid + 1;
        else
            top = mid;
    }
    if (top < bottom) return not_present;
    else {
        position = bottom;
        the_list.retrieve(bottom, data);
        if (data == target) return success;
        else return not_present;
    }
}

Error_code recursive_binary_2(const Ordered_list& the_list, const Key& target,
    int bottom, int top, int& position)
    /*
    Pre:  The indices bottom to top define the
          range in the list to search for the target.
    Post: If a Record in the range from bottom to top in the_list
          has key equal to target, then position locates
          one such entry, and a code of success is returned.
          Otherwise, not_present is returned, and position is undefined.
    Uses: recursive_binary_2, together with methods from the classes
          Ordered_list and Record.
    */
{   
    Record data;
    if (bottom <= top) {
        int mid = (bottom + top) / 2;
        the_list.retrieve(mid, data);
        if (data == target) {
            position = mid;
            return success;
        }

        else if (data < target)
            return recursive_binary_2(the_list, target, mid + 1, top, position);
        else
            return recursive_binary_2(the_list, target, bottom, mid - 1, position);
    }
    else return not_present;
}

Error_code run_recursive_binary_2(const Ordered_list& the_list,
    const Key& target, int& position)
{   
    return recursive_binary_2(the_list, target, 0, the_list.size() - 1, position);
}

Error_code binary_search_2(const Ordered_list& the_list,
    const Key& target, int& position)
    /*
    Post: If a Record in the_list has key equal to target, then position locates
          one such entry and a code of success is returned.
          Otherwise, not_present is returned and position is undefined.
    Uses: Methods for classes Ordered_list and Record.
    */
{   
    Record data;
    int bottom = 0, top = the_list.size() - 1;
    while (bottom <= top) {
        position = (bottom + top) / 2;
        the_list.retrieve(position, data);
        if (data == target) return success;
        if (data < target) bottom = position + 1;
        else top = position - 1;
    }
    return not_present;
}

void print_out(std::string msg, const double& time, const int& comparisons, const int& searches)
{
    cout.precision(6);
    cout << "Status: " << msg << endl
        << "Elapsed per search: " << fixed << time << endl
        << "Compairisons per search: " << comparisons << endl
        << "Searches: " << searches << endl << endl;
}

int chooseVersion()
{
    int userChoise;

    bool acceptable = false;

    while (true)
    {

        cout << "Welcome to Search / Sorting Algorithms.\n\n"
            << "1: Part 1: Sequence Search\n"
            << "2: Part 2: Binary Search\n"
            << "3: Part 3: Insertion Sort\n"
            << "4: Part 4: Quick Sort\n"
            << "Input: "
            << flush;

        if (cin >> userChoise)
        {
            if (userChoise == 1 || userChoise == 2 || userChoise == 3 || userChoise == 4 || userChoise == 5)
            {
                return userChoise;
            }
        }
        else
        {
            // clear error from cin so it works correctly when asking again.
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }

    return userChoise;
}