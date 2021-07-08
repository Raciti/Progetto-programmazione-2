#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Pizza{

    private:
    string nome;
    float prezzo;
    int quantità;

    public:
    Pizza(){}

    Pizza(string nome,int quantità, float prezzo){
        this->nome = nome;
        this->quantità = quantità;
        this->prezzo = prezzo;
    }

    void somma_quantità(int x){
        quantità += x;
    }

    string get_nome(){
        return nome;
    }

    int get_quantità(){
        return quantità;
    }

    float get_prezzo(){
        return prezzo;
    }

    float totale(){
        return quantità * prezzo;
    }
};

class Cliente{

    private:
    string nome;
    vector<Pizza> pizze;
    float media;

    public:
    Cliente(){}

    Cliente(string nome){
        this->nome = nome;
        media = 0.0;
    }

    void ins(Pizza p, int x){
        if(x == 0) pizze.push_back(p);
        else{
            bool trovata = false;
            for (int i = 0; i < pizze.size(); i++)
            {
                if(pizze[i].get_nome() == p.get_nome()){
                    trovata = true;
                    pizze[i].somma_quantità(p.get_quantità());
                }
            }
            if(!trovata) pizze.push_back(p);
        }
    }

    string get_nome(){
        return nome;
    }

    void print(){
        cout<<"Il cliente è: "<< nome<<endl;
        cout<<"Le pizze sono: ";
        for (int i = 0; i < pizze.size(); i++){
           cout<<pizze[i].get_nome();
           if(i == pizze.size()-1) cout << ". \n";
           else cout <<", ";
        }
    }

    float totale(){
        float Totale = 0.0;
        for (int i = 0; i < pizze.size(); i++){
            Totale += pizze[i].totale();
        }
        return Totale;
    }

    void richiesta(){
        print();
        cout<<"Il totale è: "<< totale() <<" €."<<endl;
    }

    void richiesta3(){
        cout<<"Il cliente ha ordinato le seguenti pizze: ";
        for (int i = 0; i < pizze.size(); i++){
           cout<<pizze[i].get_nome();
           if(i == pizze.size()-1) cout << " ";
           else cout <<", ";
        }
        cout<<"per un totale di "<<totale() << "€"<<endl;
    }

    void richiesta4(ostream &out){
        out<<"Il cliente è: "<< nome<<endl;
        out<<"Le pizze sono: ";
        for (int i = 0; i < pizze.size(); i++){
           out<<pizze[i].get_nome();
           if(i == pizze.size()-1) out << ". \n";
           else out <<", ";
        }
        out<<"Il totale è: "<< totale() <<" €."<<endl;
    }
    void calcola_media(){
        float tot = totale();
        media = tot / pizze.size()-1;
    }

    float getMedia(){
        calcola_media();
        return media;
    }
    //calcola_media e getMedia non sono utlizzate per la soluzione
};

int main(){
    ifstream in;
    ofstream out;
    in.open("Comande.txt");
    out.open("output.txt");

    vector<Cliente> l;
    vector<Pizza> P; //Per la soluzione bonus

    for(int task = 0; task < 59; task++){

        //INIZIO RICHIESTA 1
        string comanda;
        in >> comanda;
        string nome;
        string pizza;
        int quantità;
        float prezzo;

        int cont = 0; // usato come variabile per gestire i casi
        int pos = 0; // usato per mettersi nella prima posizione 
        int caratteri = 0; // usato per contare i caratteri da estrarre
        for (int i = 0; i < comanda.length(); i++){
            if(comanda[i] == ',' && cont == 0){
                nome = comanda.substr(0,i);
                pos = i;
                cont++;
                caratteri = 0;
            }
            else if(comanda[i] == ',' && cont == 1){
                pizza = comanda.substr(pos+1,caratteri-1);
                pos = i;
                cont++;
                caratteri = 0;
            }
            else if(comanda[i] == ',' && cont == 2){
                string tmp = comanda.substr(pos+1,caratteri-1);
                quantità = stoi(tmp); //metodo per convertire una stringa in intero
                pos = i;
                cont++;
                caratteri = 0;
            
            }
            else if(cont == 3){
                string tmp = comanda.substr(pos+1,comanda.length()-1);
                prezzo = stof(tmp); //metodo per convertire una stringa in float
                pos = i;
                cont++;
                caratteri = 0;
            }
            caratteri++;
        }
        //FINE RICHIESTA 1

        //INIZIO RICHIESTA 2
        Cliente C = Cliente(nome);
        Pizza p = Pizza(pizza, quantità, prezzo);

        //Soluzione Bonus
        bool trovatop = false;
        int contp = 0;
        for (int i = 0; i < P.size(); i++){
            if(p.get_nome() == P[i].get_nome()){
                trovatop = true;
                contp = i;
            }
        }
        if(trovatop == false){
            P.push_back(p);
        }
        else{ //Se lo trovo aggrego la nuova pizza alla lista
            P[contp].somma_quantità(p.get_quantità());
        }
        //Fine soluzione Bonus
        bool trovato = false;
        int cont2 = 0;
        //Cerco il cliente nella lista
        for (int i = 0; i < l.size(); i++){
            if(C.get_nome() == l[i].get_nome()){
                trovato = true;
                cont2 = i;
            }
        }
        //Se non lo trovo lo inserisco per la prima volta
        if(trovato == false){
            C.ins(p, 0);
            l.push_back(C);
        }
        else{ //Se lo trovo aggrego la nuova pizza alla lista
            l[cont2].ins(p, 1);
        }
       
        //FINE RICHIESTA 2  
    }

    //INIZIO RICHIESTA 3    
    string ricerca;
    cout<<"Soluzione 3° quesito"<<endl;
    cout<<"Inserire nome cliente: ";
    cin >> ricerca;
    bool find = false;
    for (int i = 0; i < l.size(); i++){
        if(l[i].get_nome() == ricerca){
            l[i].richiesta3();
            find = true;
        }
    }
    if(!find) cout<<"Cliente non trovato."<<endl;
    //FINE RICHIESTA 3

    //INIZIO RICHIESTA 4
    float media = 0.0;
    float tot = 0.0;
    for (int i = 0; i < l.size(); i++){
        tot += l[i].totale();
    }
    media = tot / l.size()-1;
    cout << endl;
    cout<<"Soluzione 4° quesito"<<endl;
    cout << "IL conto medio è di: "<< media << endl;
    cout << endl;
    if (l[0].totale() < media){
        l.erase(l.begin());
    }
    for (int i = 0; i < l.size(); i++){
        if(l[i].totale() < media){
            l.erase(l.begin() + i);
            i = 0;
        }
    }    
    //Salva sul file le ordinazioni sopra la media
    for (int i = 0; i < l.size(); i++){
        l[i].richiesta4(out); //Salvo su un file esterno i clienti che hanno
                              //Speso più della media
    }
    //FINE RICHIESTA 4

    //INIZIO RICHIESTA 5
    cout<<"Soluzione 5° quesito"<<endl;
    cout<<"Le pizze in ordine di vendite sono: "<<endl;
    for (int i = 0; i < P.size(); i++)
    {
        Pizza tmp = Pizza("c",0,0);
        int indice = 0;
        for (int j = 0; j < P.size(); j++)
        {
            if(tmp.get_quantità() < P[j].get_quantità()){
                tmp = P[j];
                indice = j;
            }
        }
        cout<<tmp.get_nome()<<" con "<<tmp.get_quantità()<<" acquisti."<<endl;
        P.erase(P.begin() + indice); 
        i = 0;
    }
    //FINE RICHIESTA 5
    in.close();
    out.close();
    return 0;
}