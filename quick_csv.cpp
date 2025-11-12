#include<bits/stdc++.h>
using namespace std;

struct Movie {
    string name;
    double rating;
    int year;
    int popularity;

    void display() {
        cout << " " + name << " | Rating: " << rating
             << " | Year: " << year << " | Popularity: "
             << popularity << endl;
    }
};

bool comparebyRating(Movie &a, Movie &b) { return a.rating < b.rating; }
bool comparebyYear(Movie &a, Movie &b) { return a.year < b.year; }
bool comparebyPopularity(Movie &a, Movie &b) { return a.popularity < b.popularity; }

void generateMovies(vector<Movie> &movies, int n) {
    vector<string> sample = {
        "Interstellar","Batman","IronMan","Superman","Avatar","Men In Black","spider-man"
    };
    srand(time(0));
    for (int i = 0; i < n; i++) {
        Movie m;
        m.name = sample[rand() % sample.size()] + " #" + to_string(i + 1);
        m.year = rand() % 45 + 1980;
        m.rating = (rand() % 90 + 10) / 10.0;  // fixed small bug here
        m.popularity = rand() % 1000000 + 1000;
        movies.push_back(m);
    }
}

void loadMoviesFromCSV(vector<Movie> &movies, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string name, ratingStr, yearStr, popStr;

        getline(ss, name, ',');       // title
        getline(ss, ratingStr, ',');  // rating
        getline(ss, yearStr, ',');    // release_year
        getline(ss, popStr, ',');     // popularity

        Movie m;
        m.name = name;
        m.rating = stod(ratingStr);
        m.year = stoi(yearStr);
        m.popularity = stoi(popStr);
        movies.push_back(m);
    }
    file.close();
}

int partition(vector<Movie> &movies, int low, int high, bool(*compare)(Movie &, Movie &)) {
    int i = low;
    int j = high;
    while (i < j) {
        while (i <= high - 1 && compare(movies[i], movies[low])) {
            i++;
        }
        while (j >= low + 1 && !compare(movies[j], movies[low])) {
            j--;
        }
        if (i < j)
            swap(movies[i], movies[j]);
    }
    swap(movies[j], movies[low]);
    return j;
}

void quickSort(vector<Movie> &movies, int low, int high, bool(*compare)(Movie &, Movie &)) {
    if (low < high) {
        int pi = partition(movies, low, high, compare);
        quickSort(movies, low, pi - 1, compare);
        quickSort(movies, pi + 1, high, compare);
    }
}

int main() {
    vector<Movie> movies;
    int n;
    string choice;
    cout << "Do you want to (1) generate random movies or (2) import from CSV? ";
    cin >> choice;

    if (choice == "2") {
        string filename;
        cout << "Enter CSV filename (e.g., movies.csv): ";
        cin >> filename;
        loadMoviesFromCSV(movies, filename);
        n = movies.size();
    } else {
        cout << "How many movie you want to generate: ";
        cin >> n;
        generateMovies(movies, n);
    }

    if (movies.empty()) {
        cout << "No movies available!" << endl;
        return 0;
    }

    string sort_by;
    cout << "Sort by (rating/year/popularity): ";
    cin >> sort_by;

    bool (*compare)(Movie &, Movie &);
    if (sort_by == "rating")
        compare = comparebyRating;
    else if (sort_by == "year")
        compare = comparebyYear;
    else if (sort_by == "popularity")
        compare = comparebyPopularity;
    else {
        cout << "Invalid choice. Defaulting to rating.\n";
        compare = comparebyRating;
    }

    clock_t start = clock();
    quickSort(movies, 0, movies.size() - 1, compare);
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        movies[i].display();
    }

    cout << "Time Taken: " << time_taken << endl;

    return 0;
}
