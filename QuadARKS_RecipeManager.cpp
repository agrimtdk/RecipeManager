#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void recipe_adder(const string& a, const string& b, const string& c, const string&d, ofstream& tracker)
{
    //to add the recipe details by usage of delimeter of ','
    tracker << a << "," << b << "," << c << "," << d << endl;
}

void delete_recipe(const string& filename, const string& recipeName) {
    //to check if the filename provided is correct
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    //creating vector to hold strings
    vector<string> lines;
    string line;
    while (getline(infile, line)) {
        //check if the line contains the recipe name, npos means not found
        if (line.find(recipeName) == string::npos) {
            lines.push_back(line);
        }
        else{
            cout << "\nRecipe not found!!!\n";
        }
    }
    infile.close();
    //to check if the file can be opened
    ofstream outfile(filename);
    if (!outfile) {
        cout << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }
    //writes the recipes to the file
    for (const auto& l : lines) {
        outfile << l << endl;
    }
    outfile.close();
}

int main() 
{
    ifstream file("<file_path>.csv");
    // Open the output file stream in append mode
    ofstream tempFile("<file_path>.csv", ios::app);
    string rec_name, rec_type, rec_ing, rec_steps;
    char choice;
    cout << "Enter 'a' to add a recipe: ";
    choice = getchar();
    if(choice == 'a' || choice == 'A')
    {
    //adding part of the recipe
    string rec_add_name, rec_add_type, rec_add_ing, rec_add_steps;
    cout << "Enter the recipe you want to add (name, type, ingredients): \n";
    cout << "Enter the recipe name: ";
    getchar();
    getline(cin, rec_add_name, '\n');
    cout << "Enter the recipe type: ";
    getline(cin, rec_add_type, '\n');
    cout << "Enter the recipe ingredients: ";
    getline(cin, rec_add_ing, '\n');
    cout << "Enter the recipe steps: ";
    getline(cin, rec_add_steps, '\n');
    recipe_adder(rec_add_name, rec_add_type, rec_add_ing, rec_add_steps, tempFile);

    }
    //deletion part of the recipe
    cout << "Enter 'd' to delete a recipe: ";
    cin >> choice;
    if(choice == 'd' || choice == 'D')
    {
    string filename = "<file_path>.csv";
    
    string recipeNameToDelete;
    cout << "Enter the name of the recipe you want to delete: ";
    getchar();
    getline(cin, recipeNameToDelete);

    delete_recipe(filename, recipeNameToDelete);
    }
    file.close();
    tempFile.close();
    
    return 0;
}

