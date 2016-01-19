#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#include <iterator>



using namespace std;
using namespace boost::filesystem;


class bagli_liste{
    public:
    bagli_liste(){this->sonraki=NULL;};
    string veri;
    bagli_liste* sonraki;

};

class eleman{

public :
    string isim;
    string d_gunu;
    string telefon;
    string adres;
    string e_posta;
    string ehliyet;
    string dil;
    double tecrube;
    int yas;
    vector<string> dil_liste;
    long int agirlik;
    vector<string> ehliyet_dizi;

    bagli_liste* egitim;
    bagli_liste* is;

    eleman* sag;
    eleman* sol;

    void olustur(string);
    double tecrube_hesapla();
    vector<string> dil_ayirma();
    int yas_hesapla();
    vector<string> ehliyet_ayirma();
};

double eleman::tecrube_hesapla(){
    bagli_liste *tmp = this->is;
    int a=1;
    double deneyim=0;
    while( tmp != NULL){

        if(a%4==0){
            deneyim += stod(tmp->veri);
        }
        tmp=tmp->sonraki;
        a++;
    }
    delete tmp;
    return deneyim;

}

int eleman::yas_hesapla(){
    int yas;
    string tmp = this->d_gunu;
    yas = stoi(tmp);
    yas = 2016-yas;
    return yas;

}

vector<string>eleman::dil_ayirma(){

    /*
   Kaynak kod:
    http://stackoverflow.com/a/890229
 */
        string next;
        vector<string> dil;
        for (string::const_iterator it = this->dil.begin(); it != this->dil.end(); it++) {

            if ( *it == ' ' ) {

                if ( !next.empty()) {

                    dil.push_back(next);
                    next.clear();
                }
            }
            else {

                next += *it;
            }
        }
        if ( !next.empty())
            dil.push_back(next);

        return dil;

}

vector<string>eleman::ehliyet_ayirma(){
  /*
   Kaynak kod:
    http://stackoverflow.com/a/890229
 */
        string next;
        vector<string> ehliyet;
        for (string::const_iterator it = this->ehliyet.begin(); it != this->ehliyet.end(); it++) {

            if ( *it == ' ' ) {

                if ( !next.empty()) {

                    ehliyet.push_back(next);
                    next.clear();
                }
            }
            else {

                next += *it;
            }
        }
        if ( !next.empty())
            ehliyet.push_back(next);

        return ehliyet;

}

void eleman::olustur(string klasor){

    std::ifstream okuma(klasor+"\\bilgi.txt");
    vector <string> veri;
    string tmp;
    while(!okuma.eof()){

        getline(okuma,tmp);
        veri.push_back(tmp);
    }
    this->agirlik=0;
    for(auto c:veri[0]){
        this->agirlik+=long(c);

    }
    this->isim=veri[0];
    this->d_gunu=veri[1];
    this->telefon=veri[2];
    this->adres=veri[3];
    this->e_posta=veri[4];
    this->ehliyet=veri[5];
    this->dil=veri[6];

    this->yas = yas_hesapla();
    this->dil_liste=dil_ayirma();
    this->ehliyet_dizi=ehliyet_ayirma();
    okuma.close();
    okuma.open(klasor+"\\egitim.txt");
    veri.clear();
    while(!okuma.eof()){

        getline(okuma,tmp);
        veri.push_back(tmp);
    }

    this->egitim = new bagli_liste;
    bagli_liste* gecici = new bagli_liste;
    gecici= this-> egitim;

    for(string deger:veri){
        gecici->veri=deger;
        gecici->sonraki=new bagli_liste;
        gecici=gecici->sonraki;
    }
    gecici=NULL;

    okuma.close();
    okuma.open(klasor+"\\is.txt");
    veri.clear();
    while(!okuma.eof()){

        getline(okuma,tmp);
        veri.push_back(tmp);
    }

    this->is=new bagli_liste;
    bagli_liste* gecici1=new bagli_liste;
    gecici1=this->is;

    for(string deger:veri){
        gecici1->veri=deger;
        gecici1->sonraki=new bagli_liste;
        gecici1=gecici1->sonraki;
    }
    gecici1=NULL;

    this->tecrube = tecrube_hesapla();

    this->sag = NULL;
    this->sol = NULL;



}

void dugum_ekle(eleman *&kok, eleman *&eklenen){
    if(kok == NULL){
        kok = new eleman;
        kok = eklenen;
    }else {
        if(eklenen->agirlik <= kok->agirlik){
            if(kok->sol == NULL){
                kok->sol = new eleman;
                kok->sol = eklenen;

            }else{
                dugum_ekle(kok->sol, eklenen);
            }
        }else {
            if(kok->sag == NULL){
                kok->sag = new eleman;
                kok->sag = eklenen;
            }else{
                dugum_ekle(kok->sag, eklenen);
            }
        }
    }
}

vector<string> eleman_listeleme(eleman *kok){
    vector<string> ret;
    if(kok != NULL){

        vector<string> v1 = eleman_listeleme(kok->sol);

        cout<<"Isim    : "<<kok->isim<<endl;
        cout<<"Sehir   : "<<kok->adres<<endl;
        cout<<"Telefon : "<<kok->telefon<<endl;
        cout<<"E-posta : "<<kok->e_posta<<endl;
        cout<<"D.Gunu  : "<<kok->d_gunu<<endl;
        cout<<"Dil     : "<<kok->dil<<endl;
        cout<<"Ehliyet : "<<kok->ehliyet<<endl;
        ret.push_back(kok->isim);

        bagli_liste* tmp=kok->egitim;

        int a=0;
        cout<<endl;

        cout<<"Okullar : ";

        while( tmp != NULL){

            if(a%6==0){
                cout<<endl;
            }
            cout<<(tmp->veri)<<" ";
            tmp=tmp->sonraki;
            a++;
        }
        cout<<endl;

        bagli_liste* tmp1=kok->is;

        a=0;

        cout<<"Isler : ";

        while( tmp1 != NULL){

            if(a%4==0){
                cout<<endl;
            }
            cout<<(tmp1->veri)<<" ";
            tmp1=tmp1->sonraki;
            a++;
        }


        cout<<endl<<"=========================================================="<<endl;

        vector<string> v2 = eleman_listeleme(kok->sag);
        ret.insert(ret.end(), v1.begin(), v1.end());
        ret.insert(ret.end(), v2.begin(), v2.end());
        return ret;

    }
    ret.clear();
    return ret;
}

void eleman_arama(eleman *kok, string aranan){


    if(kok != NULL){

        eleman_arama(kok->sol,aranan);




        if(aranan == kok->isim){

                cout<<"Isim    : "<<kok->isim<<endl;
                cout<<"Sehir   : "<<kok->adres<<endl;
                cout<<"Telefon : "<<kok->telefon<<endl;
                cout<<"E-posta : "<<kok->e_posta<<endl;
                cout<<"D.Gunu  : "<<kok->d_gunu<<endl;
                cout<<"Dil     : "<<kok->dil<<endl;
                cout<<"Ehliyet : "<<kok->ehliyet<<endl;

                bagli_liste* tmp=kok->egitim;

                int a=0;
                cout<<endl;

                cout<<"Okullar : ";

                while( tmp != NULL){

                    if(a%6==0){
                        cout<<endl;
                    }
                    cout<<(tmp->veri)<<" ";
                    tmp=tmp->sonraki;
                    a++;
                }
                cout<<endl;
                bagli_liste* tmp1=kok->is;

                a=0;

                cout<<"Isler : ";

                while( tmp1 != NULL){

                    if(a%4==0){
                        cout<<endl;
                    }
                    cout<<(tmp1->veri)<<" ";
                    tmp1=tmp1->sonraki;
                    a++;
                }



        }


        eleman_arama(kok->sag,aranan);
    }

}

vector<string> egitim_durumana_gore(eleman *kok,int tur){
    vector<string> ret;
    if(kok!=NULL){
        vector<string> v1= egitim_durumana_gore(kok->sol,tur);

        if(tur == 1 ){
            while(kok->egitim != NULL){
                    if(kok->egitim->veri == "Lise"){
                                cout<<kok->isim<<"  ";
                                ret.push_back(kok->isim);
                    }
                    kok->egitim = kok->egitim->sonraki;
            }

        }
         else if(tur == 2 ){
                while(kok->egitim != NULL){
                        if(kok->egitim->veri == "Yuksek Okul"){
                                    cout<<kok->isim<<"  ";
                                    ret.push_back(kok->isim);
                       }
                        kok->egitim = kok->egitim->sonraki;

                }

        }
        else if(tur == 3 ){
                while(kok->egitim != NULL){
                    if(kok->egitim->veri == "Lisans"){
                                cout<<kok->isim<<"  ";
                                ret.push_back(kok->isim);
                    }
                    kok->egitim = kok->egitim->sonraki;

                }

        }
        else if(tur == 4 ){
                while(kok->egitim != NULL){
                    if(kok->egitim->veri == "Yuksek Lisans"){
                                cout<<kok->isim<<"  ";
                                ret.push_back(kok->isim);
                    }
                    kok->egitim = kok->egitim->sonraki;

                }

        }
        else if(tur == 5 ){
                while(kok->egitim != NULL){
                    if(kok->egitim->veri == "Doktora"){
                                cout<<kok->isim<<"  ";
                                ret.push_back(kok->isim);
                    }
                    kok->egitim = kok->egitim->sonraki;

                }

        }




        vector<string> v2 = egitim_durumana_gore(kok->sag,tur);
        ret.insert(ret.end(), v1.begin(), v1.end());
        ret.insert(ret.end(), v2.begin(), v2.end());
        return ret;
    }
    ret.clear();
    return ret;

}

vector<string> dil_secim_listele(eleman *kok,string aranan){
    vector<string> ret;
    if(kok !=NULL){
        vector<string> v1 = dil_secim_listele(kok->sol,aranan);

        for(string d:kok->dil_liste){
            if( aranan == d){
                cout<<kok->isim<<" ";
                ret.push_back(kok->isim);
            }

        }


        vector<string> v2 = dil_secim_listele(kok->sag,aranan);
        ret.insert(ret.end(), v1.begin(), v1.end());
        ret.insert(ret.end(), v2.begin(), v2.end());
        return ret;
    }
    ret.clear();
    return ret;

}

vector<string> dile_gore_listele(eleman *kok){
    vector<string> ret;
    if(kok != NULL){
        vector<string> v1 = dile_gore_listele(kok->sol);


        vector<string> dil;
        dil=kok->dil_liste;

        int a;
        a=dil.size();


        if(a>1){
            cout<<kok->isim<<"  ";
            ret.push_back(kok->isim);
        }
        dil.clear();

        vector<string> v2 = dile_gore_listele(kok->sag);
        ret.insert(ret.end(), v1.begin(), v1.end());
        ret.insert(ret.end(), v2.begin(), v2.end());
        return ret;

    }
    ret.clear();
    return ret;

}

int derinlik(eleman * kok){
    /*
     Kaynak kod
        http://stackoverflow.com/questions/13015709/finding-depth-of-binary-tree
    */
    if(kok!=NULL){
        return 1+max(derinlik(kok->sol),derinlik(kok->sag));
    }
    return 0;
}

vector<string> tecrubeye_gore_listele(eleman *kok,double deger){
    vector<string> ret;
    if(kok != NULL){
        vector<string> v1 = tecrubeye_gore_listele(kok->sol,deger);
        if(deger <= kok->tecrube){
            cout<<kok->isim<<" ";
            ret.push_back(kok->isim);
        }
        vector<string> v2 = tecrubeye_gore_listele(kok->sag,deger);
        ret.insert(ret.end(), v1.begin(), v1.end());
        ret.insert(ret.end(), v2.begin(), v2.end());
        return ret;

    }
    ret.clear();
    return ret;


}

vector<string> deneyimsiz_listele(eleman *kok){
    vector<string> ret;
    if(kok != NULL){
        vector<string> v1 = deneyimsiz_listele(kok->sol);
        if(kok->tecrube==0){
            cout<<kok->isim;
            ret.push_back(kok->isim);
        }
        vector<string> v2 = deneyimsiz_listele(kok->sag);
        ret.insert(ret.end(), v1.begin(), v1.end());
        ret.insert(ret.end(), v2.begin(), v2.end());
        return ret;
    }
    ret.clear();
    return ret;
}

vector<string> yasa_gore_listele(eleman *kok,int deger){
    vector<string> ret;
    if(kok != NULL){
        vector<string> v1 = yasa_gore_listele(kok->sol,deger);
        if(deger >= kok->yas){
            cout<<kok->isim<<" ";
            ret.push_back(kok->isim);
        }
        vector<string> v2 = yasa_gore_listele(kok->sag,deger);
        ret.insert(ret.end(), v1.begin(), v1.end());
        ret.insert(ret.end(), v2.begin(), v2.end());
        return ret;
    }
    ret.clear();
    return ret;
}

vector<string> ehliyet_secim_listele(eleman *kok,string aranan){
    vector<string> ret;
    if(kok !=NULL){
        vector<string> v1 = ehliyet_secim_listele(kok->sol,aranan);

        for(string d:kok->ehliyet_dizi){
            if( aranan == d){
                cout<<kok->isim<<" ";
                ret.push_back(kok->isim);
            }

        }
        vector<string> v2 = ehliyet_secim_listele(kok->sag,aranan);
        ret.insert(ret.end(), v1.begin(), v1.end());
        ret.insert(ret.end(), v2.begin(), v2.end());
        return ret;
    }
    ret.clear();
    return ret;
}

vector<string> filtre ;

vector<string> filtreleme (vector<string> gelen){
    /*
    Kaynak kod :
        http://stackoverflow.com/questions/19483663/vector-intersection-in-c
        */


    if(filtre.empty()){
        filtre=gelen;
        return filtre;
    }
    else{
        sort(gelen.begin(), gelen.end());
        sort(filtre.begin(), filtre.end());

        set_intersection(gelen.begin(),gelen.end(),filtre.begin(),filtre.end(),back_inserter(filtre));

        return filtre;
    }


}

void yazma_f(eleman *kok,vector<string> filt){
        if(kok !=NULL){
        yazma_f(kok->sol,filt);
        for(string d: filt){
                if(d == kok->isim){
                    std::ofstream yazma ("C:\\Users\\Tuðrul\\Desktop\\pro_lab_2\\sirket_girisi\\"+d+".txt");
                    yazma<<"Isim    : "<<kok->isim<<endl;
                    yazma<<"Sehir   : "<<kok->adres<<endl;
                    yazma<<"Telefon : "<<kok->telefon<<endl;
                    yazma<<"E-posta : "<<kok->e_posta<<endl;
                    yazma<<"D.Gunu  : "<<kok->d_gunu<<endl;
                    yazma<<"Dil     : "<<kok->dil<<endl;
                    yazma<<"Ehliyet : "<<kok->ehliyet<<endl;

                    bagli_liste* tmp=kok->egitim;

                    int a=0;
                    yazma<<endl;

                    yazma<<"Okullar : ";

                    while( tmp != NULL){

                        if(a%6==0){
                            yazma<<endl;
                        }
                        yazma<<(tmp->veri)<<" ";
                        tmp=tmp->sonraki;
                        a++;
                    }
                    yazma<<endl;
                    bagli_liste* tmp1=kok->is;

                    a=0;

                    yazma<<"Isler : ";

                    while( tmp1 != NULL){

                        if(a%4==0){
                            yazma<<endl;
                        }
                        yazma<<(tmp1->veri)<<" ";
                        tmp1=tmp1->sonraki;
                        a++;
                    }


                }

        }

        yazma_f(kok->sag,filt);

    }

}

int main()
{




    string veri_yol="C:\\Users\\Tuðrul\\Desktop\\pro_lab_2\\asdasdasd\\eleman\\";

    eleman *kok = NULL;

    directory_iterator klasor_son;

    for(directory_iterator i(veri_yol); i!=klasor_son;i++){

        if(!is_regular_file(i->path())){

            eleman* dugum = new eleman;
            dugum->olustur(i->path().string());

            dugum_ekle(kok, dugum);
        }
    }


    vector<string>test;
    char d= 'h';
    do{

        int secim;
        cout<<"Yapmak istediginiz islemi seciniz..."<<endl;
        cout<<"Ise basvuran tum adaylarin bilgileri icin        1"<<endl
            <<"Adindan kisi arama tum bilgileri listeleme icin  2"<<endl
            <<"Okudugu okul duzeyine gore adaylarin adlari icin 3"<<endl
            <<"Dile gore adlarin listelenmesi icin              4"<<endl
            <<"Birden fazla dil bilenlerin listesi icin         5"<<endl
            <<"Deneyim suresine gore kisilerin listesi icin     6"<<endl
            <<"Deneyimsiz kisilerin listesi icin                7"<<endl
            <<"Yas degerinin altindakilerin listesi icin        8"<<endl
            <<"Belirli tip ehliyeti olan kisilerin listesi icn  9"<<endl;
        cin>>secim;

        string aranan;
        int tur;
        double deger;


            if(secim==1){
                  test = eleman_listeleme(kok);
                  filtreleme(test);
            }
            else if(secim==2){
                cout<<endl<<"Arananin ismini giriniz : ";
                cin.ignore();
                getline(cin,aranan);
                eleman_arama(kok,aranan);
            }
            else if(secim==3){
                cout<<endl<<"Listelemek istediginiz turu giriniz  "<<endl;
                cout<<"Lise icin 1"<<endl
                    <<"Yuksek Okul icin 2"<<endl
                    <<"Lisans icin 3"<<endl
                    <<"Yuksek Lisans icin 4"<<endl
                    <<"Doktora icin 5"<<endl;
                cin>> tur;
                test = egitim_durumana_gore(kok,tur);
                filtreleme(test);

            }
            else if(secim==4){
                cout<<endl<<"Aranan dili giriniz : ";
                cin.ignore();
                getline(cin,aranan);
                test = dil_secim_listele(kok,aranan);
                filtreleme(test);
            }
            else if(secim==5){
                test = dile_gore_listele(kok);
                filtreleme(test);
            }
            else if(secim==6){
                cout<<"Alt tecrube sinirini giriniz : ";
                cin>>deger;
                test = tecrubeye_gore_listele(kok,deger);
                filtreleme(test);
            }
            else if(secim==7){
                test = deneyimsiz_listele(kok);
                filtreleme(test);
            }
            else if(secim==8){
                cout<<"Yas sinirini giriniz : ";
                cin>>deger;
                test = yasa_gore_listele(kok,deger);
                filtreleme(test);
            }
            else if(secim==9){
                cout<<endl<<"Aranan ehliyeti giriniz : ";
                cin.ignore();
                getline(cin,aranan);
                test = ehliyet_secim_listele(kok,aranan);
                filtreleme(test);
            }




        cout<<endl<<"Filtrelemeye devam etmek istiyor musunuz ? (e,h)";
        cin>>d;


    }while(d=='e' or d=='E');


        char f ;
        cout<<"Filtrelediginiz elemanlari ayri dosyada tutmak ister misiniz ? (e,h)";
        cin>>f;
        if(f == 'e' or f == 'E'){
            yazma_f(kok,test);

        }
        char s;
        cout<<"Tutulan dosyalari silmek istiyor musunuz ? (e,h)";
        cin>>s;
        if(s=='e' or 'E'){
            for(string d : test){
                remove(d+".txt");
            }
        }


    return 0;
}
