#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>

using std::fstream;

void mips_decoder(std::vector<int> binary);
int bin_to_num(std::vector<int> bin, int begin, int end);


struct rForm{
	int opCode = 0;
	int RS;
	int RT;
	int RD;
	int shift_amount;
	int func;
};

struct iForm{
	int opCode;
	int RS;
	int RD;
	int imm;
};

struct jForm{
	int opCode;
	int address;
};

int main() {
    std::vector<unsigned int> vs;

    fstream input("mips-test.bin", fstream::binary | fstream::in);

    unsigned int v;
    while(input.read(reinterpret_cast<char*>(&v), sizeof(v)))
        vs.push_back(v);

    input.close();


    int i = 0;
    while(i != 10){
    	unsigned int bnr = vs[i];
    	std::vector<int> a(32);
    	for(int x = 0; bnr>0; ++x){
    		a[x] = bnr%2;
    		bnr = bnr/2;
    	}
    	++i;
    	mips_decoder(a);
    	
    }

    return 0;

   
}


void mips_decoder(std::vector<int> binary){

	//Detect R, I, or J
	int opCode = 0;
	for(int i = 0; i != 6; ++i){
		if(binary[i] == 1){
			int powhelper = (5-i);
			opCode += pow(2, powhelper);
		}
	}


	//R FORMAT 
	if(opCode == 0){
		rForm x;

		
		//RS DECODER
		int begin = 6;
		int end = 11;
		x.RS = bin_to_num(binary, begin, end);

		//RT DECODER
		begin = 11;	end = 16;
		x.RT = bin_to_num(binary, begin, end);

		//RD DECODER
		begin = 16; end = 21;
		x.RD = bin_to_num(binary, begin, end);

		//Shift Amount DECODER
		begin = 21; end = 26;
		x.shift_amount = bin_to_num(binary, begin, end);

		//FUNCTION DECODER
		begin = 26; end = 32;
		x.func = bin_to_num(binary, begin, end);

		using std::cout;
		using std::endl;
		cout<<endl<<"Here are the values for your R format Registers."<<endl;
		cout<<x.RS<<endl<<x.RT<<endl<<x.RD<<endl<<x.shift_amount<<endl<<x.func<<endl;
		
	}
	
	//J FORMAT
	else if(opCode == 2 || opCode == 3){
		jForm j;
		j.opCode = opCode;

		int begin = 11; int end = 32;
		j.address = bin_to_num(binary, begin, end);

		using std::cout;
		using std::endl;
		cout<<endl<<"Here are the values for your J format Registers."<<endl;
		cout<<j.opCode<<endl<<j.address<<endl;

	}


	//I FORMAT
	else{
		iForm i;
		i.opCode = opCode;

		//DECODE RS
		int begin =6; int end = 11;
		i.RS = bin_to_num(binary, begin, end);

		//DECODE RD
		begin = 11; end = 16;
		i.RD = bin_to_num(binary, begin, end);

		begin = 16; end = 32;
		i.imm = bin_to_num(binary, begin, end);	

		using std::cout;
		using std::endl;
		cout<<endl<<"Here are the values for your I format Registers."<<endl;
		cout<<i.opCode<<endl<<i.RS<<endl<<i.RD<<endl<<i.imm<<endl;
	}
	
	
	
}



//THIS FUNCTION RECEIVES THE BINARY VECTOR, + BEGIN AND END SECTIONS
//TO CREAT A SUBVECTOR FOR EACH SECTION OF THE RJI FORMS.
//IT RETURNS A DECIMAL VALUE BASED ON THE BINARY ENCODED IN THE VECTOR
int bin_to_num(std::vector<int> bin, int begin, int end){

	//MAKE NEW VECTOR USING RANGE SPECIFIED BY BEGIN AND END
	std::vector<int> newBin(bin.begin() + begin, bin.begin() + end);

	//GET SIZE FOR BINARY CONVERSION
	int size = newBin.size()-1;
	int binNum = 0;
	
	for(unsigned int i = 0; i < newBin.size(); ++i){
		if(newBin[i] == 1){
			int helper = size-i;
			binNum += pow(2, helper);
		}
	}

	return binNum;
}