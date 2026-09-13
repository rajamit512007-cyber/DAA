// Amit Raj
// 25/DA/011
#include <iostream>
#include <algorithm>
using namespace std;

struct Activity {
    int start, finish, index;
};

bool activityCompare(Activity a1, Activity a2) {
    return (a1.finish < a2.finish);
}

void printMaxActivities(Activity arr[], int n) {

    sort(arr, arr + n, activityCompare);

    cout << "Selected Activities: \n";


    int i = 0;
    cout << "Activity " << arr[i].index
         << " -> Start: " << arr[i].start
         << ", Finish: " << arr[i].finish << endl;


    for (int j = 1; j < n; j++) {
        
        if (arr[j].start >= arr[i].finish) {
            cout << "Activity " << arr[j].index
                 << " -> Start: " << arr[j].start
                 << ", Finish: " << arr[j].finish << endl;
            i = j;
        }
    }
}

int main() {
    int n;
    cout << "Enter number of activities: ";
    cin >> n;

    Activity arr[n];
    cout << "Enter start and finish time of each activity:\n";
    for (int i = 0; i < n; i++) {
        cout << "Activity " << i + 1 << " Start Finish: ";
        cin >> arr[i].start >> arr[i].finish;
        arr[i].index = i + 1;
    }

    cout << "\n--- Result ---\n";
    printMaxActivities(arr, n);

    return 0;
}