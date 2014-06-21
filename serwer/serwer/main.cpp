#include "Serwer.h"

using namespace std;

int main(){
	try{
		Serwer *s = new Serwer();
		s->connection();
	}
	catch (string w){
		cout << w << endl;
	}
	return 0;
}
