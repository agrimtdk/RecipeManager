#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits> 

using namespace std;
const int days = 7;
const int meals = 3;
string daysOfWeek[days] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
struct Recipe
{
    vector<string> recipe;
    int m = 0;
};

Recipe add_line_in_vector(const string &line)
{
    Recipe recipe;
    stringstream get(line);
    string temp;
    while (getline(get, temp, ','))
    {
        if (temp != "directions")
        {
            recipe.m++; // Count the number of ingredients
        }
        else
        {
            // Stop parsing ingredients when "directions" is encountered
        }
        recipe.recipe.push_back(temp);
    }
    return recipe;
}

void searchRecipe(const string &file_name, const string &recipe_name)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        cout << "ERROR: File is not open!" << endl;
        return;
    }
    string line;
    Recipe recipe;
    int flag = 0;
    while (getline(file, line))
    {
        recipe = add_line_in_vector(line);
        if (recipe_name == recipe.recipe[0])
        {
            flag = 1; // Recipe found
            cout << "Recipe Name: " << recipe.recipe[0] << endl;
            cout << "Category: " << recipe.recipe[1] << endl;
            cout << "Ingredients:" << endl;
            for (int i = 2; i < recipe.recipe.size(); ++i)
            {
                if (recipe.recipe[i] == "directions")
                {
                    cout << "Directions :" << endl;
                }
                else if (recipe.recipe[i] == "Directions :")
                {
                    continue;
                }
                else
                    cout << "-"<<recipe.recipe[i] << endl;
            }

            break; // No need to continue searching after finding the recipe
        }
    }
    if (flag == 0)
    {
        cout << "Recipe not found." << endl;
    }
    file.close();
}
void display_recipe_category(const string &file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "ERROR: File is not open!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Recipe recipe = add_line_in_vector(line);
        cout << "Recipe: " << recipe.recipe[0] << " - Category: " << recipe.recipe[1] << endl;
    }
    
    file.close();
}
