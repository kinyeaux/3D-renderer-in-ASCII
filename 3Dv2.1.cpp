//made by 3ch0kwa1
#include <ncurses.h>
#include <bits/stdc++.h>
#include <cmath>
#include <time.h>
#include <unistd.h>

using namespace std;

class vec3d{
public:

	double x;
	double y;
	double z;

	vec3d(double a, double b, double c){
		x = a;
		y = b;
		z = c;
	}
	
	vec3d operator + (const vec3d& v){
		return vec3d(x+v.x, y+v.y, z+v.z);
	}
	
	vec3d operator - (const vec3d& v){
		return vec3d(x-v.x, y-v.y, z-v.z);
	}
	
	vec3d operator * (double lambda){
		return vec3d(x*lambda, y*lambda, z*lambda);
	}
	
	double operator * (const vec3d& v){
		return x*v.x + y*v.y + z*v.z;
	}
	
	vec3d operator % (const vec3d& v){
		return vec3d(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	}
	
	vec3d rotate (const double alpha, const char* c){
		if(c == "x"){
			double y1 = cos(alpha) * y + sin(alpha) * z;
			double z1 = - sin(alpha) * y + cos(alpha) * z;
			return vec3d(x, y1, z1);
		}
		
		if(c == "y"){
			double z1 = cos(alpha) * z + sin(alpha) * x;
			double x1 = - sin(alpha) * z + cos(alpha) * x;
			return vec3d(x1, y, z1);
		}
		
		if(c == "z"){
			double x1 = cos(alpha) * x + sin(alpha) * y;
			double y1 = - sin(alpha) * x + cos(alpha) * y;
			return vec3d(x1, y1, z);
		}
		
		return vec3d(x, y, z);
	}
	
	double len(){
		return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	}
	
	vec3d normalize(){
		return vec3d(x / sqrt(pow(x,2) + pow(y,2) + pow(z,2)),
					 y / sqrt(pow(x,2) + pow(y,2) + pow(z,2)),
					 z / sqrt(pow(x,2) + pow(y,2) + pow(z,2)));
	}
	
	void print(){
		std::cout << x << ' ' << y << ' ' << z << '\n';	
	}
};

bool isnumber(char c){
	string str = "0123456789";
	for(char cc: str){
		if(cc == c) return true;
	}
	return false;
}

int main(){
	char nev[60];
	cin >> nev;
	const char* name = &nev[0];
	
	string shadows = "$@%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'.";
	vec3d camera = vec3d(0.0, 0.0, 1.0);
	vec3d cameraposition = vec3d(0.0, 0.0, -20.0);
	
    initscr();
    noecho();
    
    int maxlines = LINES-1, maxcols = COLS-1;  //getting window parameters
    
    int xcenter = maxlines/2, ycenter = maxcols/2;   //setting the center of the window
    
    double p = 10.0;
    
    double pi = 3.141592653;
					   
	vector<vec3d> points;
	vector<pair<int,int>> lines;
	vector<vector<int>> faces;
    
    wmove(stdscr, xcenter, ycenter);
							   
	string num = "0123456789ABCDEFG";
							   
	ifstream fin(name);
    
    while(!fin.eof()){
		string vertex;
		getline(fin, vertex);
		
		if(vertex[0] == 'v' && vertex[1] == ' '){
			stringstream ss(vertex);
			string v;
			double aa, bb, cc;
			ss >> v >> aa >> bb >> cc;
			points.push_back(vec3d(aa, bb, cc));
		}
		
		if(vertex[0] == 'f'){
			stringstream ss(vertex);
			string v;
			ss >> v;
			vector<string> s;
			vector<int> a;
			
			while(!ss.eof()){
				ss >> v;
				s.push_back(v);
			}
			
			for(string str: s){
				stringstream sss(str);
				string token;
				getline(sss, token, '/');
				stringstream ssss(token);
				int g;
				ssss >> g;
				a.push_back(g-1);
			}
			
			vector<int> faces0;
			for(int i=0;i<a.size()-1;i++){
				lines.push_back({a[i],a[i+1]});
				faces0.push_back(a[i]);
			}
			lines.push_back({a[0],a[a.size()-1]});
			faces0.push_back(a[a.size()-1]);
			faces.push_back(faces0);
		}
	}
    
    fin.close();
    
    int peaks = points.size();
    int edges = lines.size();
    int sides = faces.size();
    
    for(int i=0;i<points.size();i++) points[i] = points[i]*(p);
	
	double modulus = 100.0;
	
	bool rotation = true;
	
	vector<pair<int,double>> facedistances;
    
    while(true){
		
		wclear(stdscr);
		
		for(int i=0;i<peaks;i++){
			if(rotation){
				points[i] = points[i].rotate(0.1, "x");
				points[i] = points[i].rotate(0.2, "y");
				points[i] = points[i].rotate(-0.2, "z");
			}	
		}
		
		int kb;
		timeout(1);
		kb = getch();
		if(kb == 120){
			for(int i=0;i<peaks;i++) points[i] = points[i]*1.2;
		}
		if(kb == 121){
			for(int i=0;i<peaks;i++) points[i] = points[i]*0.8;
		}
		if(kb == 27){
			endwin();
			return 0;
		}
		if(kb == 113){ //q
			for(int i=0;i<peaks;i++) points[i] = points[i].rotate(0.1, "x");
		}
		if(kb == 97){ //a
			for(int i=0;i<peaks;i++) points[i] = points[i].rotate(-0.1, "x");
		}
		if(kb == 119){ //w
			for(int i=0;i<peaks;i++) points[i] = points[i].rotate(0.1, "y");
		}
		if(kb == 115){ //s
			for(int i=0;i<peaks;i++) points[i] = points[i].rotate(-0.1, "y");
		}
		if(kb == 101){ //e
			for(int i=0;i<peaks;i++) points[i] = points[i].rotate(0.1, "z");
		}
		if(kb == 100){ //d
			for(int i=0;i<peaks;i++) points[i] = points[i].rotate(-0.1, "z");
		}
		if(kb == 114) rotation = !rotation;
		
		facedistances.clear();
		vec3d sulypont = vec3d(0.0, 0.0, 0.0);
		for(int i=0;i<sides;i++){
			for(int j=0;j<faces[i].size();j++){
				sulypont = sulypont + points[faces[i][j]];
			}
			sulypont = sulypont * (double) (1.0  / faces[i].size());
			facedistances.push_back({i, sulypont.z - cameraposition.z});
		}

		sort(facedistances.begin(),facedistances.end(),[](auto a, auto b){return a.second<b.second;});
		
		/*for(int i=0;i<sides;i++){
			cout << facedistances[i].first << " " << facedistances[i].second << '\n';
		}*/

		for(int i=0;i<sides;i++){
			vec3d line1 = points[faces[facedistances[i].first][1]] - points[faces[facedistances[i].first][0]];
			vec3d line2 = points[faces[facedistances[i].first][faces[facedistances[i].first].size()-1]] - points[faces[facedistances[i].first][0]];
			vec3d facenormal = line1 % line2;
			facenormal = facenormal.normalize();
			double multiple = abs(facenormal * camera);
			int brightness = (int) ((1-multiple)*66);

			for(int j=1;j<faces[facedistances[i].first].size()-1;j++){
				for(double k=0.01;k<1.0;k+=(0.05/modulus)){
					vec3d a = points[faces[facedistances[i].first][j]] - points[faces[facedistances[i].first][0]];
					vec3d b = points[faces[facedistances[i].first][j+1]] - points[faces[facedistances[i].first][j]];
					vec3d d = b * k;
					vec3d c = a + d;
					for(double l=0.01;l<1.0;l+=(0.05/modulus)){
						vec3d f = c * l;
						vec3d e = f + points[faces[facedistances[i].first][0]];
						if(e.z - cameraposition.z > 10.0){
							modulus = 100.0 / (e.z - cameraposition.z);
							
							if(abs(e.x * modulus) <= maxlines/2 && abs(e.y * modulus) <= maxcols/4){
								wmove(stdscr, xcenter - e.x * modulus, ycenter + 2 * e.y * modulus);
								if(winch(stdscr) == 32) waddch(stdscr, shadows[brightness]);
							}
						}
					}
				}
			}
		}
		
		
			
		refresh();
		usleep(150000);
		
	}
	
    endwin();

    return 0;
}
