#ifndef SINTAKSNO_CPP
#define SINTAKSNO_CPP

#include <iostream>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

class ASTCvor {
    private:
    public:
        virtual ~ASTCvor(){}
        virtual int interpretiraj(map<string, int>& mapa) = 0;
        virtual void show() = 0;
        virtual ASTCvor* clone() = 0;
};

class ProgramCvor : public ASTCvor{
    private:
        vector<ASTCvor*> naredbe;
    public:
        ProgramCvor(){}
        ProgramCvor(ProgramCvor& p){
            for(auto naredba : p.naredbe){
                   naredbe.push_back(naredba->clone());
            }
        }
        ~ProgramCvor(){}
        int interpretiraj(map<string, int>& mapa){
            for(auto naredba : naredbe){
                naredba->interpretiraj(mapa);
            }
            return 0;
        }
        void show(){
            for(auto naredba : naredbe){
                naredba->show();
                cout << ';' << endl;
            }
        }
        ASTCvor* clone(){
            return new ProgramCvor(*this);
        }

        void dodaj(ASTCvor* cvor){
            naredbe.push_back(cvor);
        }
};

class IdCvor : public ASTCvor{
    private:
        string _ime;
    public:
        IdCvor(string& ime) : _ime(ime){}
        IdCvor(IdCvor& p){
            _ime = p._ime;
        }
        ~IdCvor(){}
        int interpretiraj(map<string, int>& mapa){
            if(mapa.find(_ime) == mapa.end()){
                exit(EXIT_FAILURE);
            }

            return mapa[_ime];
        }
        void show(){
            cout << _ime;
        }
        ASTCvor* clone(){
            return new IdCvor(*this);
        }
};

class BinarniOpCvor : public ASTCvor{
    private:
        ASTCvor* _l, *_d;
        string _op;
    public:
        BinarniOpCvor(ASTCvor* l, const string& op, ASTCvor* d) : _l(l), _op(op), _d(d){}
        BinarniOpCvor(BinarniOpCvor& p){
            _op = p._op;
            _l = p._l->clone();
            _d = p._d->clone();
        }
        ~BinarniOpCvor(){
            delete _l;
            delete _d;
        }
        int interpretiraj(map<string, int>& mapa){
            int l = _l->interpretiraj(mapa);
            int d = _d->interpretiraj(mapa);

            if(_op == "+"){
                return l + d;
            }
            if(_op == "-"){
                return l - d;
            }
            if(_op == "*"){
                return l * d;
            }
            if(_op == "/"){
                return l / d;
            }
            if(_op == "%"){
                return l % d;
            }
            if(_op == "&"){
                return l & d;
            }
            if(_op == "|"){
                return l | d;
            }
            if(_op == "^"){
                return l ^ d;
            }
            if(_op == "<<"){
                return l << d;
            }
            if(_op == ">>"){
                return l >> d;
            }
            return 0;
        }
        void show(){
            _l->show();
            cout << _op;
            _d->show();
        }
        ASTCvor* clone(){
            return new BinarniOpCvor(*this);
        }
};

class UnarniOpCvor : public ASTCvor{
    private:
        char _op;
        ASTCvor* _c;
    public:
        UnarniOpCvor(ASTCvor* c, char op) : _c(c), _op(op){}
        UnarniOpCvor(UnarniOpCvor& p){
            _op = p._op;
            _c = p._c->clone();
        }
        ~UnarniOpCvor(){
            delete _c;
        }
        int interpretiraj(map<string, int>& mapa){
            int c = _c->interpretiraj(mapa);

            if(_op == '-'){
                return -c;
            }
            if(_op == '~'){
                return ~c;
            }
            return 0;
        }
        void show(){
            cout << _op;
            _c->show();
        }
        ASTCvor* clone(){
            return new UnarniOpCvor(*this);
        }
};

class LogickeOpCvor : public ASTCvor{
    private:
        ASTCvor* _l, *_d;
        string _op;
    public:
        LogickeOpCvor(ASTCvor* l, const string& op, ASTCvor* d) : _l(l), _op(op), _d(d){}
        LogickeOpCvor(LogickeOpCvor& p){
            _op = p._op;
            _l = p._l->clone();
            _d = p._d->clone();
        }
        ~LogickeOpCvor(){
            delete _l;
            delete _d;
        }
        int interpretiraj(map<string, int>& mapa){
            int l = _l->interpretiraj(mapa);
            int d = _d->interpretiraj(mapa);

            if(_op == ">"){
                cout << (l > d ? "True" : "False") << endl;
            }
            if(_op == "<"){
                cout << (l < d ? "True" : "False") << endl;
            }
            if(_op == "=="){
                cout << (l == d ? "True" : "False") << endl;
            }
            if(_op == "!="){
                cout << (l != d ? "True" : "False") << endl;
            }
            if(_op == ">="){
                cout << (l >= d ? "True" : "False") << endl;
            }
            if(_op == "<="){
                cout << (l <= d ? "True" : "False") << endl;
            }
            return 0;
        }
        void show(){
            _l->show();
            cout << _op;
            _d->show();
        }
        ASTCvor* clone(){
            return new LogickeOpCvor(*this);
        }
};

class ZagradeCvor : public ASTCvor{
    private:
        ASTCvor* _c;
    public:
        ZagradeCvor(ASTCvor* c) : _c(c){}
        ZagradeCvor(ZagradeCvor& p){
            _c = p._c->clone();
        }
        ~ZagradeCvor(){
            delete _c;
        }
        int interpretiraj(map<string, int>& mapa){
            return _c->interpretiraj(mapa);
        }
        void show(){
            cout << "(";
            _c->show();
            cout << ")";
        }
        ASTCvor* clone(){
            return new ZagradeCvor(*this);
        }
};

class DodelaCvor : public ASTCvor{
    private:
        string _ime;
        ASTCvor* _izraz;
        bool _b;
    public:
        DodelaCvor(ASTCvor* izraz, string& ime, bool b) : _izraz(izraz), _ime(ime), _b(b){}
        DodelaCvor(string& ime, bool b) : _ime(ime), _b(b){}
        DodelaCvor(DodelaCvor& p){
            _ime = p._ime;
            _izraz = p._izraz->clone();
            _b = p._b;
        }
        ~DodelaCvor(){
            delete _izraz;
        }
        int interpretiraj(map<string, int>& mapa){
            if(_b == true){
                if(mapa.find(_ime) != mapa.end()){
                    exit(EXIT_FAILURE);
                }
                
                if(_izraz == nullptr){
                    mapa[_ime] = 0;
                } else{
                    mapa[_ime] = _izraz->interpretiraj(mapa);
                }
            } else{
                if(mapa.find(_ime) == mapa.end()){
                    exit(EXIT_FAILURE);
                }
                
                mapa[_ime] = _izraz->interpretiraj(mapa);
            }
            return 0;
        }
        void show(){
            if(_b == true){
                cout << "def " << _ime;
                if(_izraz != nullptr){
                    cout << " = ";
                    _izraz->show();
                }
            } else{
                cout << _ime << " = ";
                _izraz->show();
            }
        }
        ASTCvor* clone(){
            return new DodelaCvor(*this);
        }
};

class PrintCvor : public ASTCvor{
    private:
        char _c;
        ASTCvor* _izraz;
    public:
        PrintCvor(ASTCvor* izraz, char c) : _izraz(izraz), _c(c){}
        PrintCvor(PrintCvor& p){
            _c = p._c;
            _izraz = p._izraz->clone();
        }
        ~PrintCvor(){
            delete _izraz;
        }
        int interpretiraj(map<string, int>& mapa){
            int vrednost = _izraz->interpretiraj(mapa);
            if(_c == 'b'){
                cout << bitset<8>(vrednost) << endl;
            } else if (_c == 'd'){
                cout << dec << vrednost << endl;
            } else if(_c == 'h'){
                cout << hex << vrednost << dec << endl;
            }
            return 0;
        }
        void show(){
            cout << "print (\"%" << _c << "\", ";
            _izraz->show();
            cout << ")";
        }
        ASTCvor* clone(){
            return new PrintCvor(*this);
        }
};

class BrojCvor : public ASTCvor{
    private:
        int _x;
    public:
        BrojCvor(int x) : _x(x){}
        BrojCvor(BrojCvor& p){
            _x = p._x;
        }
        int interpretiraj(map<string, int>& mapa){
            return _x;
        }
        void show(){
            cout << _x;
        }
        ASTCvor* clone(){
            return new BrojCvor(*this);
        }
};

#endif



