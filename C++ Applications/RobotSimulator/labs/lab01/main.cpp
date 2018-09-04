// adapted from http://umich.edu/~eecs381/handouts/filestreams.pdf

// This follows the Google Style Guide:
//    https://google.github.io/styleguide/cppguide.html
// Style correctness verified by cpplint (pip install cpplint)

// Copyright 2017 <Amy Larson>"

#include <iostream>
#include <fstream>
#include <string>

int main() {
  
  // instantiate an output stream object with filename "private.pvt"
  // If the file exists, it will be deleted and recreated.
  std::string fname = "private.pvt";
  std::ofstream privateFile(fname);
  if (!privateFile.is_open()) {
    // Something went wrong - report and abort.
    std::cout << "ERROR: output file " << fname << " could not be opened."
      << std::endl;
    return 1;
  }

  // Populate the file
  privateFile << "The list of things I need to do" << std::endl;
  privateFile << std::endl;
  for (int i = 1; i < 11; i++) {
    privateFile << "Do item #" << i << "." << std::endl;
  }

  privateFile.close();

  // instantiate an output stream object with filename "shared.md"
  // If the file exists, it will be deleted and recreated.
  fname = "shared.md";
  std::ofstream sharedFile(fname);
  if ( !sharedFile.is_open() ) {
    // Something went wrong. Report and Abort.
    std::cout << "ERROR: output file " << fname << " could not be opened."
      << std::endl;
    return 1;
  }

  // Populate the file
  sharedFile <<
  "# This is a heading for documentation of my lab." << std::endl <<
  "Lab01 Github Basics creates two files." << std::endl <<
  "The private file will not be tracked via git, but this will." << std::endl;
  sharedFile << std::endl <<
  "If you want to learn more about Markdown, which is an " << std::endl <<
  "html-like language for creating the readme.md file that " << std::endl <<
  "every repo should have and probably most directories too," << std::endl <<
  "see " <<
    "https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet";
  sharedFile << std::endl;

  sharedFile.close();

  // Report to the user all was successful
  std::cout <<
    "The private.pvt and shared.md files should now be in your directory!";
  std::cout << std::endl;

  return 0;
}
