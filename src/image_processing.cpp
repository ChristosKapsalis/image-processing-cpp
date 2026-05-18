#include <iostream>
#include <vector> //gia dunamiki desmeusi xwrou mesw vector
#include <ctime> //Gia tin eisagwgi tuxaiwn timwn ston pinaka-eikonas
#include <iomanip> //Gia tin eksodo setw((4)
using namespace std;

class pixel //klasi gia kathe pixel
{
	private:
		unsigned char value; //anti gia int pou tha epiane 4 bits xrisimopoiw unsigned char gia elafrunsi tou programmatos 
	public:
		pixel(unsigned char v=0); //constructor
		unsigned char getValue() const; //getter
		void setValue(unsigned char v); //setter
		void Brightness_manage(int delta); //Auksomeiwsi fwteinotitas
		void reverse_colour();	//Antistrofi xrwmatos	
};

class image //klasi eikonas
{
	private:
		int width; //platos
		int height;	//mikos
		vector<vector<pixel>> pixels; //dynamikos 2D pinakas vector
	public:
		image(int w, int h); //Constructor
		pixel getPixel(int x, int y) const; //Getter pixel
		void setPixel(int x, int y, pixel p); //setter pixel
		void Brightness_manage(int delta); //Rithmizei th fwt olis tis eikonas
		void printImage() const; //gia ektypwsh	
		void reverse_colour(); //Antistrefei to xrwma
};

int main()
{
	int choice;
	int width, height;
	cout<<"Dwse platos eikonas: ";
	cin>>width;
	cout<<"Dwse upsos eikonas: ";
	cin>>height;
	
	image test(width,height); //orismos tou apothikeumenou arxeiou eikonas klasis image
	
	do{
		cout<<"------------------------\n";
		cout<<"----------MENU----------\n";
		cout<<"------------------------\n";
		cout<<"Choose option 1 to 6:\n";
		cout<<"1. Eisagwgi pinaka eikonas\n";
		cout<<"2. Automath eisagwgi tuxaiou pinaka eikonas\n";
		cout<<"3. Epeksergasia Fwteinotitas\n";
		cout<<"4. Antistrofh Xrwmatwn\n";
		cout<<"5. Ektypwsh Pinaka eikonas\n";
		cout<<"6. Exit\n";
		cout<<"Epilogh: ";
		cin>>choice;
		cout<<"\n\n\n";
		
		if((choice>6)||(choice<1))
		{
			cout<<"Lathos Epilogi!!! Dokimase ksana.\n";
			continue;
		}
		switch(choice)
		{
			case 1:
				for (int y = 0; y < height; y++)
				{
					for (int x = 0; x < width; x++) {
			            int val;
			            cout << "Pixel[" << y << "][" << x << "] = ";
			            cin >> val;
			            unsigned char brightness=static_cast<unsigned char>(val); //metatrepei se un char
						pixel p(brightness); //Dimiourgia pixel
						test.setPixel(x,y,p); //Apothikeush stin eikona
	        		}
				}
				break;	
						
			case 2:
			{
				srand(time(0));
				for(int y=0; y<height; y++)
				{
					for(int x=0;x<width;x++)
					{
						int random=rand()%256;
						unsigned char brightness=static_cast<unsigned char>(random); //metatrepei se un char
						pixel p(brightness); //Dimiourgia pixel
						test.setPixel(x,y,p); //Apothikeush stin eikona
					}
				}
				break;
			}
			
			case 3:
				{
					int delta;
					cout<<"Dwse timi auksisis'+'/meiwsis'-' fwteinotitas: ";
					cin>>delta;
					test.Brightness_manage(delta);
					cout<<"H fwteinotita allakse me "<<delta<<"monades.\n";
				}
				break;
			
			case 4:
				test.reverse_colour();
				cout<<"Antistrafikan ta xrwmata!\n";
				break;
				
			case 5:
				cout<<"Pinakas eikonas: \n";
				test.printImage();
				cout<<"\n\n\n";
				break;
			
			case 6:
				cout<<"Exiting..."<<endl;
				break;
		
		}
	} while(choice!=6);
	
	return 0;
}

//Swmata sunartisewn tis class pixel

pixel::pixel(unsigned char v) //Swma constructor gia arxikopoihsh fwteinotitas
{
	value=v;
}

unsigned char pixel::getValue() const //gia epistrofi timis
{
	return value;
}

void pixel::setValue(unsigned char v) //orizei nea timi
{
	value=v;
}

void pixel::Brightness_manage(int delta) //metavoli fwteinotitas kata +/- delta pou dinei o xristis
{
	int temp=value+delta;
	if(temp>255)
		temp=255;
	if(temp<0)
		temp=0;
	value=temp;
}

void pixel::reverse_colour()
{
	value=255-value; //antistrefei to xrwma enos pixel
}

//Swmata sunartisewn tis class image

image::image(int w,int h) //constructor
{
	width=w;
	height=h;
	pixels=vector<vector<pixel>>(height, vector<pixel>(width));
}

pixel image::getPixel(int x, int y) const //getter statheros
{
	return pixels[y][x];
}

void image::setPixel(int x, int y, pixel p) //setter 
	{
		pixels[y][x]=p;
	}

void image::Brightness_manage(int delta) //metavoli fwt gia ola ta pixels tou pinaka
{
	for(int x=0; x<height; x++)
	{
		for(int y=0; y<width; y++)
		{
			pixels[y][x].Brightness_manage(delta);
		}
	}
}

void image::printImage() const //ektupwsi tou pinaka-eikonas
{
	for(int x=0; x<height; x++)
	{
		for(int y=0; y<width; y++)
		{
			cout<<setw(4)<<(int)pixels[y][x].getValue()<<" ";
		}
		cout<<endl;
	}
}

void image::reverse_colour() //antistrofi tou xrwmatos olwn twn pixels
{
	for(int x=0;x<height;x++)
	{
		for(int y=0;y<width;y++)
		{
			pixels[y][x].reverse_colour();
		}
	}
}
