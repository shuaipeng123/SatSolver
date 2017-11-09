#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <tuple>
#include <vector>
#include <math.h>
using namespace std;
#include "Proposition.h"
template <typename Out>
void split(const std::string &s, char delim, Out result) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}
void permutation(std::vector<int> bar);
void shortest_path(int, int, int, int);

bool build_points_from_E(int);
void rule1(int vertice_number,int vc_size);
void rule2(int vertice_number,int vc_size);
void rule4(int point);
std::vector<int> points1;
std::vector<std::string> nums;
std::vector<Proposition> line;
// std::ifstream infile("test.txt");
int main(int argc, char **argv) {
  // Test code. Replaced with your code

  // Print command line arguments that were used to start the program

  // separator character
  // read from stdin until EOF
  int dp;
  int sp;
  int vertice_number;
  unsigned num;

  int length = 0;
  bool flag_v = true;
  bool flag_s = true;
  bool flag_e = true;
  while (!std::cin.eof()) {
    // std::cout << "Enter numbers separated by comma: ";
    std::string line;
    std::getline(std::cin, line);
    // cout << line << endl;
    std::istringstream input(line);
    if (line.size() <= 0) {
      if (std::cin.eof()) {
        std::cerr  << "EOF\n";
      } else {
        std::cerr << "Error:in shortest path no input\n";
      }
    } else {
	
      char ch;
      input >> ch;
      ws(input);

      if (input.fail()) {
        std::cerr << "Error:in shortest path  need to parse a character\n";
      }

      if (ch == 'V' && flag_v) {
	//std::cout<<line<<std::endl;
	 nums.clear();
  	points1.clear();
        // parse an integer
        input >> num;

        if (input.fail()) {
          std::cerr << "Error:in shortest path  need to parse a number\n";
          break;
        } else {
          vertice_number = num+1;
	  rule1(vertice_number,ceil(vertice_number/2.0));
	  rule2(vertice_number,ceil(vertice_number/2.0));
          flag_v = true;
        }
        // if eof bail out

      } // end V
      else if (ch == 's' && flag_s) {
        // read a character
        // Note that whitespace is ignored
        std::vector<int> sp_dp;
        while (!input.eof()) {
          if (input.eof()) {
            std::cerr << "Error:in shortest path Unexpected argument\n";
            break;
          }

          // parse an integer
          input >> num;
          if (input.fail()) {
            std::cerr << "Error:in shortest path no starting point\n";
            break;
          } else {
            sp_dp.push_back(num);
            flag_s = false;
          }
        }

        sp = sp_dp.at(0);
        dp = sp_dp.at(1);
        if (sp >= vertice_number || dp >= vertice_number) {
          flag_s = true;
	   flag_e = true;
          flag_v = true;
          std::cerr << "Error: in shortest path wrong input format for s\n";
        } else {
          shortest_path(vertice_number, length, sp, dp);
          flag_s = true;
          flag_e = true;
          flag_v = true;
        }
      } // end s if
      else if (ch == 'E' && flag_e) {
	//std::cout<<line<<std::endl;
        nums = split(line, ',');
        // done parsing a line, print the numbers
        length = nums.size();
	/*
        if (length == 1) {
          std::cout
              << "Warning:Since there are no edges, no path can be in this "
                 "graph\n";
        }
	*/
        if (!nums.empty() && length != 1) {

          bool flag_point = build_points_from_E(vertice_number);
	 
          if (!flag_point) {
            points1.clear();
            std::cerr << "Error: in shortest path  wrong input for E\n";
          } else
		{
		int count=1;
		for (std::vector<int>::iterator it = points1.begin() ;
        	it != points1.end(); ++it) {
		
			rule4((*it+1));
			if(count%2==0)
				std::cout<<std::endl;
			count++;	
		}
	            flag_e = true;
		}
        }

      } else
        std::cerr << "Error:in shortest path  wrong input\n"<<std::flush;
    }
  }
}


void rule1(int vertice_number,int vc_size){
	int index=1;
	std::cout<<"rule 1 VN:"<<vertice_number<<std::endl;
	std::cout<<"rule 1 VCS:"<<vc_size<<std::endl;
	//std::list<std::vector<int>> ckln;
	
	
 
    
	for(int i=1;i<=vertice_number;i++)
	{
		
		for(int j=1;j<=vc_size;j++)
		{	
			Proposition obj1;
    			obj1.position = index;
			obj1.index_i=i;
			obj1.index_k=j;			
			line.push_back(obj1);
			index++;
		}
		
	}
	//above build the line object for whole task
	/*
 	 for (std::vector<Proposition>::iterator it = line.begin() ;
        	it != line.end(); ++it) {

    		std::cout<<(*it).index_i<<" index_i ";
      		std::cout<<(*it).position<<" position ";
     		 std::cout<<std::endl;
    	}
	*/
	std::vector<int> bar_rule3;
	for(int i=1;i<=vc_size;i++)
	{
 	for (std::vector<Proposition>::iterator it = line.begin() ;
        	it != line.end(); ++it) {
		if(i==(*it).index_k)
    		{
			std::cout<<(*it).position;
			bar_rule3.push_back((*it).position);
			
		}      
    		}
	std::cout<<std::endl;
	permutation(bar_rule3);
	bar_rule3.clear();
	
	}
	/*
	for(int i=0;i<vc_size;i++)
	{
		
		for(int j=i;j<vertice_number*vc_size;j=j+2)
		{
			std::cout<<line.at(j)<<" ";
					
		}
		std::cout<<"0"<<std::endl;
	}
	*/					
}



void rule2(int vertice_number,int vc_size){
	
	//int index=1;
	std::cout<<"rule 2 VN:"<<vertice_number<<std::endl;
	std::cout<<"rule 2 VCS:"<<vc_size<<std::endl;
	std::vector<int> bar_rule2;
	for (std::vector<Proposition>::iterator it = line.begin() ;
        	it != line.end(); ++it) {
		if(((*it).position)%vc_size==0)
		{	
			bar_rule2.push_back((*it).position);
			//std::cout<<bar_rule2.size()<<" size "<<std::endl;
			permutation(bar_rule2);
			bar_rule2.clear();
		}
		else
			{
                        //std::cout<<((*it).position)%vc_size<<" % "<<std::endl;
			bar_rule2.push_back((*it).position);	
			}
    	}
}


void rule4(int point){
	
	//int index=1;
	//std::cout<<"rule 4 point:"<<point<<std::endl;

	
 	for (std::vector<Proposition>::iterator it = line.begin() ;
        	it != line.end(); ++it) {
		if(point==(*it).index_i)
    		{
			std::cout<<(*it).position;
			
			
		}      
    	}
	
	
	
}



//n is the size of vector
//r is the number being chosen to permute
void permutation(std::vector<int> bar){
	
 	int r=2;
	int n=bar.size();
	//std::cout<<n<<" n value"<<std::endl;
   std::vector<bool> v(n);
   std::fill(v.begin(), v.begin() + r, true);

   do {
       for (int i = 0; i < n; ++i) {
           if (v[i]) {
               std::cout << bar.at(i) << " ";
           }
       }
       std::cout << "\n";
   } while (std::prev_permutation(v.begin(), v.end()));

}



void shortest_path(int points, int length, int sp, int dp) {
  int infinity = 9999999;
  int dis[points];
  int flag[points];
  int edg[points][points];
  if (sp == dp) {
    std::cout << sp << std::endl;
    return;
  }
  if (length == 1) {
    std::cout << 0 << std::endl;
  }
  for (int i = 0; i < points; i++) {
    for (int j = 0; j < points; j++) {
      if (i == j) {
        edg[i][j] = 0;
      } else {
        edg[i][j] = infinity;
      }
    }
  }

  for (int i = 0; i < length; i = i + 2) {

    edg[points1.at(i)][points1.at(i + 1)] = 1;
    edg[points1.at(i + 1)][points1.at(i)] = 1;
  }

  // setting distance to starting point
  for (int i = 0; i < points; i++) {
    dis[i] = edg[sp][i];
  }

  // setting flag for starting point
  for (int i = 0; i < points; i++) {
    flag[i] = 0;
  }
  flag[sp] = 1;
  int min, u;
  std::vector<tuple<int, int>> first;
  for (int i = 0; i < points - 1; i++) {
    min = infinity;
    for (int j = 0; j < points; j++) {
      if (flag[j] == 0 && dis[j] < min) {
        min = dis[j];
        u = j;
      }
    }
    std::tuple<int, int> foo(u, sp);
    // int u_sp=u*10+sp;
    first.emplace_back(foo);
    flag[u] = 1;
    for (int v = 0; v < points; v++) {
      if (edg[u][v] < infinity) {

        if (dis[v] > dis[u] + edg[u][v]) {
          dis[v] = dis[u] + edg[u][v];
          std::tuple<int, int> foo(u, v);
          first.emplace_back(foo);
        }
      }
    }
  }
  // int tmp=-1;
  int tmp_dp = dp;
  if (dis[dp] != infinity) {
    std::vector<int> result;
    for (std::vector<tuple<int, int>>::iterator it = first.end() - 1;
         it != first.begin(); --it) {

      if (std::get<1>(*it) == tmp_dp) {
        // std::cout  <<std::get<0>(*it)<<"->"<<std::get<1>(*it)<<std::endl;
        result.emplace_back(tmp_dp);
        // tmp=(*it/10);
        tmp_dp = std::get<0>(*it);
        // std::cout  << tmp_dp<<"this is tmp_dp"<<std::endl;
      }
      // std::cout << ' ' <<std::get<0>(*it)<<std::get<1>(*it)<<endl;
    }
    // std::cout  << sp<<"->"<<tmp_dp<<std::endl;
    result.emplace_back(tmp_dp);
    result.emplace_back(sp);
    for (std::vector<int>::reverse_iterator it = result.rbegin();
         it != result.rend(); ++it) {
      if (it != result.rend() - 1)
        std::cout << *it << "-";
      else
        std::cout << *it<<std::endl;
    }
  } else {
    std::cout << "Error: there is no path";
  }
 
}

bool build_points_from_E(int points) {
  for (std::string x : nums) {
    std::size_t found = x.find_first_of("E{}<>");
    while (found != std::string::npos) {
      x[found] = ' ';
      found = x.find_first_of("E{}<>", found + 1);
    }
    int integer = std::stoi(x);
    points1.push_back(integer);
    if (integer >= points)
      return false;
  }
  return true;
}
