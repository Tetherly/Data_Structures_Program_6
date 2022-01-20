//  Created by Tyler Starling
//  COP4530 -- Program 6 Word, Number, and Character Usage Statistics
//  Due Date: 7/27/2021
//  STL Container Chosen: Unordered Maps

#include <iostream>
#include <unordered_map>
#include <cctype>
#include <string>

using namespace std;

void printTopTenChars(unordered_map<string, pair<int, int>> &cMap, int numberOfChars);
void printTopTenWords(unordered_map<string, pair<int, int>> &wMap, int numberOfWords);
void printTopTenNumbers(unordered_map<string, pair<int, int>> &nMap, int numberOfNumbers);

int main() {

    char reads; //  used for reading in the data, 1 char at a time

    //  counters
    int numOfChar = 0;
    int numOfWord = 0;
    int numOfNumb = 0;

    //  holds all of characters, words, and numbers that are read in
    string word;
    string ch;
    string numb;

    //  using unordered_maps to hold all of the characters, words, and numbers
    //  the first element is a string of the character, word, or number and the second
    //  is a pair with the appearance count and the order in which it was read in
    unordered_map<string, pair<int, int>> charMap;
    unordered_map<string, pair<int, int>> wordMap;
    unordered_map<string, pair<int, int>> numberMap;

    while(!cin.eof()){  //  loop until the end of file is reached   (while loop runs n times where n is the number of characters)

        cin.get(reads); //  reads in 1 char at a time
        numOfChar++;    //  this will increment every time the loop runs
        ch += reads;    //  adds the character to the character string

        if(isalpha(reads) != 0){    //  checks if the character is (a to z)
            word += tolower(reads); //  adds the character to the word string
            if(numb.length() >= 1){ //  if the last character was a number, add that number to the appropriate map
                if(numberMap.find(numb) != numberMap.end()){    //  in the case where the number is already in the map
                    ++numberMap[numb].first;    //  increase the appearance count of that number
                }
                else{   //  in the case where the number is not in the map,create a new pair with the string of the number and its appearance count being 1 with the index at numOfChar
                    numberMap.insert(make_pair(numb, make_pair(1, numOfChar)));
                    numOfNumb++;    //  increment the number of numbers the file contains
                }
                numb = "";  //  reset the number string's contents
            }
        }
        else if(isdigit(reads) != 0){   //  checks it the character is a digit (0 to 9)
            numb += reads; //  adds the character to the number string
            if(word.length() >= 1){ //  if the last character was a word, add that word to the appropriate map
                if(wordMap.find(word) != wordMap.end()){    //  in the case where the word is already in the map
                    ++wordMap[word].first;    //  increase the appearance count of that word
                }
                else{   //  in the case where the word is not in the map,create a new pair with the string of the word and its appearance count being 1 with the index at numOfChar
                    wordMap.insert(make_pair(word, make_pair(1, numOfChar)));
                    numOfWord++;    //  increment the number of words the file contains
                }
                word = "";  //  reset the word string's contents
            }
        }else{  //  when the character is neither 0 to 9 / a to z
            if(numb.length() >= 1){ //  if the previous character(s) were a number
                if(numberMap.find(numb) != numberMap.end()){    //  if the number is already in the map
                    ++numberMap[numb].first;    //  increment the appearance counter by 1
                }else{  //  if the number is unique to the map
                    numberMap.insert(make_pair(numb, make_pair(1, numOfChar))); //  add the number with its first count as 1 and the index of numOfChar
                    numOfNumb++;    //  increment the total number of numbers in the file
                }
                numb = "";  //  reset the number string
            }
            if(word.length() >= 1){ //  if the previous character(s) were a word
                if(wordMap.find(word) != wordMap.end()){    //  if the word is already in the map
                    ++wordMap[word].first;  //  increment the appearance counter of the word by 1
                }else{  //  if the word is unique to the map
                    wordMap.insert(make_pair(word, make_pair(1, numOfChar)));   //  add the word with its first count as 1 and the index of numOfChar
                    numOfWord++;    //  increment the total number of words in the file
                }
                word = "";  //  reset the word string
            }
        }

        ++charMap[ch].first;    //  adds the character to the character map
        ch = "";    //  resets the character for the next iteration of the while loop
    }   //  while loop over

    //  calls the respective print functions to display the total number of characters, words, and numbers;
    //  as well as prints the top 10 for each category
    printTopTenChars(charMap, numOfChar);
    printTopTenWords(wordMap, numOfWord);
    printTopTenNumbers(numberMap, numOfNumb);

    return 0;

}   //  end of main

//  prints the total number of characters in the file; also prints the top 10 most frequently occurring characters
void printTopTenChars(unordered_map<string, pair<int, int>> &cMap, int numberOfChars){
    auto tempMap = cMap.begin();    //  creates an iterator at the beginning of cMap
    if(numberOfChars < 10){
        numberOfChars = cMap.size();
    }else if(numberOfChars > 10){
        numberOfChars = 10;
    }else{
        //  numberOfChars is right where we want it
    }

    //  outputs the total number of characters, as well as the top ten most used characters
    cout << "In total, there are " << cMap.size() << " different characters, the " << numberOfChars << " most used characters are: " << endl;
    for(int i = 0; i < numberOfChars; i++){ //  loops the size of numberOfChars times
        int biggest = 0;
        for(auto mover = cMap.begin(); mover != cMap.end(); ++mover){   //  runs n number of times where n is the size of the unordered map
            //  this ensures that the character with the highest appearances gets picked; in the case of a tie, the character with the lowest ascii value gets picked
            if(mover->second.first > biggest || (mover->second.first == biggest && (mover->first < tempMap->first))){
                biggest = mover->second.first;  //  assign the new top used character to biggest
                tempMap = mover;    //  sets our temporary map to the unordered map we're searching through
            }
        }
        cout << "No. " << i << ": ";    //  output tidying
        //  determine if the character is a tab/newline, if so, output accordingly
        if(tempMap->first == "\n"){ //  newline
            cout << "\\n" << "          " << biggest << endl;
        }else if(tempMap->first == "\t"){   //  tab
            cout << "\\t" << "          " << biggest << endl;
        }else{  //  neither newline or tab
            cout << tempMap->first << "          " << biggest << endl;
        }
        cMap.erase(tempMap);
    }
}

//  prints the total number of words in the file; also prints the top 10 most frequently occurring words
void printTopTenWords(unordered_map<string, pair<int, int>> &wMap, int numberOfWords){
    auto tempMap = wMap.begin();    //  creates an iterator at the beginning of wMap
    if(numberOfWords < 10){
        numberOfWords = wMap.size();
    }else if(numberOfWords > 10){
        numberOfWords = 10;
    }else{
        //  numberOfWords is right where we want it
    }

    //  outputs the total number of words, as well as the top ten most used words
    cout << "In total, there are " << wMap.size() << " different words, the " << numberOfWords << " most used words are: " << endl;
    for(int i = 0; i < numberOfWords; i++){ //  loops the size of numberOfWords times
        int biggest = 0;
        //  this ensures that the word with the highest appearances gets picked; in the case of a tie, the word that appears earlier gets picked
        for(auto mover = wMap.begin(); mover != wMap.end(); ++mover){   //  runs n number of times where n is the size of the unordered map
            if(mover->second.first > biggest || (mover->second.first == biggest && (mover->second.second < tempMap->second.second))){
                biggest = mover->second.first;  //  assign the new top used word to biggest
                tempMap = mover;    //  sets our temporary map to the unordered map we're searching through
            }
        }
        //  output tidying
        cout << "No. " << i << ": " << tempMap->first << "          " << biggest << endl;
        wMap.erase(tempMap);
    }
}

//  prints the total number of numbers in the file; also prints the top 10 most frequently occurring numbers
void printTopTenNumbers(unordered_map<string, pair<int, int>> &nMap, int numberOfNumbers){
    auto tempMap = nMap.begin();    //  creates an iterator at the beginning of nMap
    if(numberOfNumbers < 10){
        numberOfNumbers = nMap.size();
    }else if(numberOfNumbers > 10){
        numberOfNumbers = 10;
    }else{
        //  numberOfNumbers is right where we want it
    }

    //  outputs the total number of numbers, as well as the top ten most used numbers
    cout << "In total, there are " << nMap.size() << " different numbers, the " << numberOfNumbers << " most used numbers are: " << endl;
    for(int i = 0; i < numberOfNumbers; i++){   //  loops the size of numberOfNumbers times
        int biggest = 0;
        //  this ensures that the number with the highest appearances gets picked; in the case of a tie, the number that appears earlier gets picked
        for(auto mover = nMap.begin(); mover != nMap.end(); ++mover){   //  runs n number of times where n is the size of the unordered map
            if(mover->second.first > biggest || (mover->second.first == biggest && (mover->second.second < tempMap->second.second))){
                biggest = mover->second.first;  //  assign the new top used number to biggest
                tempMap = mover;    //  sets our temporary map to the unordered map we're searching through
            }
        }
        //  output tidying
        cout << "No. " << i << ": " << tempMap->first << "          " << biggest << endl;
        nMap.erase(tempMap);
    }
}
