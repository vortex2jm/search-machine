# Search machine :gear:

#### Here we have two implementations of the same program to compare the efficiency

 - The first approach is using generics **red black trees**
 - The second approach is using generics **ternary search trees**

*Each one is in a different branch*

#### About
This app is divided in some parts:
 - **Indexer**: This step creates the pages tree and link the pages. All pages have links between themselves, which are important to define the page rank later;
 - **Page ranking**: It defines which page is more relevant in the result of search, in case one word is found in more than one page;
 - **Terms tree**: This tree stores all terms of all pages. Each term has a pointer to a tree containing all pages that contains this term, sorted by page ranking;
 - **Search processor**: It receives the program input, searches for a term in the _terms tree_ and print the result of search;
