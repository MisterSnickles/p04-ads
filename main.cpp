#include "utility.h"
#include "Binary_node.h"
#include "Binary_tree.h"
#include "Search_tree.h"
#include "AVL_node.h"
#include "AVL_tree.h"

/*
 * Handle command line error
 */
struct CommandLineException
{
   CommandLineException()
   {
      cout << endl;
      cout << "Incorrect command line arguments." << endl;
      cout << "The path of input file is incorrect." << endl;
      cout << "An example to execute this program:" << endl;
      cout << "    ./p04 input.dat " << endl;
   }

};

/*
 * Handle exception when openning a file
 */
struct FileException {
   FileException(const string file) {
    cout << endl << "'" << file << "'" << " could not be opened." << endl;
   }
};

/*
 * Handle unexpected file content
 */
struct FileContentException {
   FileContentException() {
      cout << endl << "The content of the file doesn't match the requirements." << endl;
      cout << "This file can't be further processed." << endl;
   }
};

int main(int argc, char** argv){
   try {
      // handle command line input
      if (argc != 2) {
         throw CommandLineException();
      }

      ifstream input_file;
      input_file.open(argv[1]);
      if (!input_file) {
         throw FileException(argv[1]);
      }

      AVL_tree<int> avl_tree;
      string line;
      while (input_file >> line) {
         int option = 0;
         if (!line.compare("insert")) {
            option = 1;
         }
         else if (!line.compare("delete")) {
            option = 2;
         }

         input_file >> line;
         if (isNumber(line)) {
            int value = string_to_int(line);
            if (option == 1) { 
               avl_tree.insert(value);
            }
            else if (option == 2) {
               avl_tree.remove(value);
            }
         }
         else {
            throw FileContentException();
         }
      }

   avl_tree.print();

   } catch (...) {
      cout << "Program ended unexpectedly." << endl;
      exit(EXIT_FAILURE);
   }

   return 0;
}