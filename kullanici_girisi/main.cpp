#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#include <iterator>


using namespace boost::filesystem;
using namespace std;



void eleman_giris(){

    vector<string> bilgi;
    vector<string> egitim;
    vector<string> is;


    string isim;
    cout<< "Isim ve soyismi giriniz : \n";
    getline(cin,isim);
    bilgi.push_back(isim);

    string d_gunu;
    cout<< "Dogum yilinizi giriniz : \n";
    getline(cin,d_gunu);
    bilgi.push_back(d_gunu);

    string telefon;
    cout<< "Telefon numaranizi giriniz : \n";
    getline(cin,telefon);
    bilgi.push_back(telefon);

    string adres;
    cout<< "Yasadiginiz sehri giriniz : \n";
    getline(cin,adres);
    bilgi.push_back(adres);

    string e_posta;
    cout<< "E-postanizi giriniz : \n";
    getline(cin,e_posta);
    bilgi.push_back(e_posta);

    string ehliyet;
    char ehliyet_secim;
    cout<< "Ehlyetiniz var mi (e,h) ? : ";
    cin>> ehliyet_secim;
    cin.ignore();

    if(ehliyet_secim=='h' or ehliyet_secim == 'H'){
            bilgi.push_back("Yok");

    }
    else{
            cout<< "Aralarina bosluk koyarak yaziniz.. : \n";
            getline(cin,ehliyet);
            bilgi.push_back(ehliyet);

    }


    string dil;
    char dil_secim;
    cout<< "Bildiginiz yabanci dil var mi ? (e,h)  : ";
    cin>> dil_secim;
    cin.ignore();
    if(dil_secim == 'h' or dil_secim == 'H'){
            bilgi.push_back("Yok");

    }
    else{

            cout<< "Aralarina bosluk koyarak yaziniz.. : \n";
            getline(cin,dil);
            bilgi.push_back(dil);

    }



    char okul_secim;
    cout<<"Okugunuz okul var mi ? (e,h) ";
    cin>>okul_secim;
    cin.ignore();

    if(okul_secim =='e' or okul_secim == 'E'){

            okul_secim == 'H';
            do{
                string tur;
                cout<< "Turunu giriniz (Lise,Yuksek Okul,Lisans,Yuksek Lisans,Doktora) : \n";
                getline(cin,tur);
                egitim.push_back(tur);

                string okul;
                cout<< "Okulun adi : \n";
                getline(cin,okul);
                egitim.push_back(okul);

                string bolum;
                cout<< "Bolumu giriniz : \n";
                getline(cin,bolum);
                egitim.push_back(bolum);

                string baslangic;
                cout<< "Baslangic tarihi giriniz : \n";
                getline(cin,baslangic);
                egitim.push_back(baslangic);

                string bitis;
                cout<< "Bitis tarihi giriniz : \n";
                getline(cin,bitis);
                egitim.push_back(bitis);

                string ortalama;
                cout<< "Mezuniyet puaninizi giriniz : \n";
                getline(cin,ortalama);
                egitim.push_back(ortalama);

                cout<< "Baska okul girmek istiyor musunuz ? (e,h) \n" ;
                cin>>okul_secim;
                cin.ignore();


            }while(okul_secim == 'e' or okul_secim == 'E');





    }

    char is_secimi;
    cout<<"Is deneyiminiz varmi ? (e,h)";
    cin>>is_secimi;
    cin.ignore();
    if(is_secimi=='e'){

            is_secimi == 'h';

            do{

                string sirket;
                cout<< "Calistiginiz sirketin adini giriniz : \n";
                getline(cin,sirket);
                is.push_back(sirket);

                string sehir;
                cout<< "Sirketin bulundugu sehri giriniz : \n";
                getline(cin,sehir);
                is.push_back(sehir);

                string pozisyon;
                cout<< "Calistiginiz pozisyonu giriniz : \n";
                getline(cin,pozisyon);
                is.push_back(pozisyon);

                string sure;
                cout<< "Calistiginiz sureyi giriniz : \n";
                getline(cin,sure);
                is.push_back(sure);


                cout<< "Baska is girmek istiyor musunuz ? (e,h) \n" ;
                cin>>is_secimi;
                cin.ignore();



            }while(is_secimi == 'e' or is_secimi == 'E');


    }

    string yol = "C:\\Users\\Tuðrul\\Desktop\\pro_lab_2\\asdasdasd\\eleman\\" + isim;
    if(!exists(yol)){
    create_directories(yol);
    }
    else{
        cout<<"Ayni isimde kayit var!!!!!";
        exit(0);

    }

    std::ofstream yazma(yol+"\\bilgi.txt");
    for(auto i : bilgi){
        yazma<<i<<endl;
    }
    yazma.close();

    yazma.open(yol+"\\egitim.txt");
     for(auto j:egitim){
        yazma<<j<<endl;
    }
    yazma.close();

    yazma.open(yol+"\\is.txt");
     for(auto k:is){
        yazma<<k<<endl;
    }


}

void okuma(string klasor){

    std::ifstream okuma(klasor+"\\bilgi.txt");
    string tmp;
    while(!okuma.eof()){

        getline(okuma,tmp);
        cout<<tmp<<endl;
    }
    okuma.close();
    okuma.open(klasor+"\\egitim.txt");
    while(!okuma.eof()){

        getline(okuma,tmp);
        cout<<tmp<<endl;
    }
    okuma.close();
    okuma.open(klasor+"\\is.txt");
    while(!okuma.eof()){

        getline(okuma,tmp);
        cout<<tmp<<endl;
    }

}

void eleman_goruntuleme(){
    string isim;
    cout<< "Isim ve soyismi giriniz : \n";
    getline(cin,isim);

    string yol = "C:\\Users\\Tuðrul\\Desktop\\pro_lab_2\\asdasdasd\\eleman\\"+isim;
    okuma(yol);

}

void eleman_silme(){

    string isim;
    cout<< "Isim ve soyismi giriniz : \n";
    getline(cin,isim);

    string yol = "C:\\Users\\Tuðrul\\Desktop\\pro_lab_2\\asdasdasd\\eleman\\"+isim;
    boost::filesystem::remove_all(yol);


}

void eleman_guncelleme(){



    string isim;
    cout<< "Isim ve soyismi giriniz : \n";
    getline(cin,isim);
    string yol = "C:\\Users\\Tuðrul\\Desktop\\pro_lab_2\\asdasdasd\\eleman\\" + isim;


    int dosya;
    cout<<"Hangi dosyanizi duzenlemek istersiniz : "<<endl
        <<"Bilgi icin  1"<<endl
        <<"Egitim icin 2"<<endl
        <<"Is icin     3"<<endl;
    cin>>dosya;
    cin.ignore();


    if(dosya==1){
        vector<string> bilgi;
        string isim;
        cout<< "Isim ve soyismi giriniz : \n";
        getline(cin,isim);
        bilgi.push_back(isim);

        string d_gunu;
        cout<< "Dogum yilinizi giriniz : \n";
        getline(cin,d_gunu);
        bilgi.push_back(d_gunu);

        string telefon;
        cout<< "Telefon numaranizi giriniz : \n";
        getline(cin,telefon);
        bilgi.push_back(telefon);

        string adres;
        cout<< "Yasadiginiz sehri giriniz : \n";
        getline(cin,adres);
        bilgi.push_back(adres);

        string e_posta;
        cout<< "E-postanizi giriniz : \n";
        getline(cin,e_posta);
        bilgi.push_back(e_posta);

        string ehliyet;
        char ehliyet_secim;
        cout<< "Ehlyetiniz var mi (e,h) ? : ";
        cin>> ehliyet_secim;
        cin.ignore();

        if(ehliyet_secim=='h' or ehliyet_secim == 'H'){
                bilgi.push_back("Yok");

        }
        else{
                cout<< "Aralarina bosluk koyarak yaziniz.. : \n";
                getline(cin,ehliyet);
                bilgi.push_back(ehliyet);

        }


        string dil;
        char dil_secim;
        cout<< "Bildiginiz yabanci dil var mi ? (e,h)  : ";
        cin>> dil_secim;
        cin.ignore();
        if(dil_secim == 'h' or dil_secim == 'H'){
                bilgi.push_back("Yok");

        }
        else{

                cout<< "Aralarina bosluk koyarak yaziniz.. : \n";
                getline(cin,dil);
                bilgi.push_back(dil);

    }

    std::ofstream yazma(yol+"\\bilgi.txt");
    for(auto i:bilgi){
        yazma<<i<<endl;
    }



    }
    else if(dosya == 2){
        vector<string> egitim;
        char okul_secim;
        cout<<"Okugunuz okul var mi ? (e,h) ";
        cin>>okul_secim;
        cin.ignore();

        if(okul_secim =='e' or okul_secim == 'E'){

                do{
                    string tur;
                    cout<< "Turunu giriniz (Lise,Yuksek Okul,Lisans,Yuksek Lisans,Doktora) : \n";
                    getline(cin,tur);
                    egitim.push_back(tur);

                    string okul;
                    cout<< "Okulun adi : \n";
                    getline(cin,okul);
                    egitim.push_back(okul);

                    string bolum;
                    cout<< "Bolumu giriniz : \n";
                    getline(cin,bolum);
                    egitim.push_back(bolum);

                    string baslangic;
                    cout<< "Baslangic tarihi giriniz : \n";
                    getline(cin,baslangic);
                    egitim.push_back(baslangic);

                    string bitis;
                    cout<< "Bitis tarihi giriniz : \n";
                    getline(cin,bitis);
                    egitim.push_back(bitis);

                    string ortalama;
                    cout<< "Mezuniyet puaninizi giriniz : \n";
                    getline(cin,ortalama);
                    egitim.push_back(ortalama);

                    cout<< "Baska okul girmek istiyor musunuz ? (e,h) \n" ;
                    cin>>okul_secim;
                    cin.ignore();


                }while(okul_secim == 'e' or okul_secim == 'E');





        }

        std::ofstream yazma(yol+"\\egitim.txt");
        for(auto j:egitim){
        yazma<<j<<endl;
        }

    }
    else if(dosya == 3){
            vector<string> is;
        char is_secimi;
        cout<<"Is deneyiminiz varmi ? (e,h)";
        cin>>is_secimi;
        cin.ignore();
        if(is_secimi=='e' or is_secimi == 'E'){

                do{

                    string sirket;
                    cout<< "Calistiginiz sirketin adini giriniz : \n";
                    getline(cin,sirket);
                    is.push_back(sirket);

                    string sehir;
                    cout<< "Sirketin bulundugu sehri giriniz : \n";
                    getline(cin,sehir);
                    is.push_back(sehir);

                    string pozisyon;
                    cout<< "Calistiginiz pozisyonu giriniz : \n";
                    getline(cin,pozisyon);
                    is.push_back(pozisyon);

                    string sure;
                    cout<< "Calistiginiz sureyi giriniz : \n";
                    getline(cin,sure);
                    is.push_back(sure);


                    cout<< "Baska is girmek istiyor musunuz ? (e,h) \n" ;
                    cin>>is_secimi;
                    cin.ignore();



                }while(is_secimi == 'e' or is_secimi == 'E');


        }
        std::ofstream yazma(yol+"\\is.txt");
        for(auto k:is){
        yazma<<k<<endl;
        }



    }

}

int main()
{
    cout<<"================================================\n";
    cout<<"BUTUN PROGRAM BOYUNCA TURKCE KARAKTER GIRMEYINIZ\n";
    cout<<"================================================\n";

    int secim;
    cout<<"Eleman giris icin       1"<<endl
        <<"Eleman goruntuleme icin 2"<<endl
        <<"Eleman silme icin       3"<<endl
        <<"Eleman guncelleme icin  4"<<endl;
    cin>>secim;
    cin.ignore();
    if(secim==1){
        eleman_giris();
    }
    else if(secim==2){
        eleman_goruntuleme();
    }
    else if(secim==3){
        eleman_silme();
    }
    else if (secim==4){
        eleman_guncelleme();
    }


    return 0;
}
