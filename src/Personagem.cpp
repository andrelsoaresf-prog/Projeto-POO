#include <string>
#include <random>

class Personagem{
protected:
int vida_;
int mana_;
std::string nome_;

public:
    Personagem(int vida, int mana, const std::string& nome)
    {set_mana(mana); set_nome(nome); set_vida(vida);}

    virtual ~Personagem() = default;

    void set_vida(int vida){
        if (vida <= 0) { vida_ = 10; }
        else { vida_ = vida; }
    }

    void set_mana(int mana){
        if (mana <= 0) { mana_ = 10; }
        else { mana_ = mana; }
    }

    void set_nome(std::string nome){
        if(nome.empty()) { nome_ = "Nome genérico";}
        else { nome_ = std::move(nome); }
    }

    void recebe_dano(int dano) {
    if (dano > 0) {
        vida_ = (vida_ - dano < 0) ? 0 : (vida_ - dano);
    }
}

    [[nodiscard]] int vida() const { return vida_; }
    [[nodiscard]] int mana() const { return mana_; }
    [[nodiscard]] const std::string nome() const { return nome_; }

    virtual int habilidadeOfensiva(int consulta) = 0;
    virtual int habilidadeDefensiva(int consulta) = 0;

    std::string ficha() {
        int cura = habilidadeDefensiva(1);
        int dano = habilidadeOfensiva(1);

        return nome_ + " agiu no turno! (Recuperou: " + std::to_string(cura) +
           " | Dano causado: " + std::to_string(dano) +
           " | HP: " + std::to_string(vida_) +
           " | Mana: " + std::to_string(mana_) + ")";
    }

    Personagem(const Personagem&) = delete;
    Personagem& operator=(const Personagem&) = delete;
};

class Mago final : public Personagem{
    int dano_magia_;

public:
    Mago(int vida, int mana, const std::string& nome, int dano) : Personagem(vida, mana, nome)
    {set_dano_magia(dano);}

    [[nodiscard]] int dano_magia() const { return dano_magia_; }

    void set_dano_magia(int dano){
        if(dano <= 0) { dano_magia_ = 10; }
        else{ dano_magia_ = dano; }
    }

    int habilidadeOfensiva(int consulta) override {
        if(consulta == 1){ return dano_magia(); }

        if(mana_ >= 10){
            mana_ -= 10;
            return dano_magia();
        }
        return 0;
    }

    int habilidadeDefensiva(int consulta) override {
        if(consulta == 1){ return 30; }

        if(mana_ >= 15){
            mana_ -= 15;
            vida_ += 30;
            return 30; 
        }
        return 0;
    }
};

class AtaqueCritico {
public:
    virtual int DanoCritico(int dano, int critico) const = 0;
    virtual ~AtaqueCritico() = default;
};

class Guerreiro final : public Personagem, public AtaqueCritico{
    int dano_arma_;
    int critico_;
public:
    Guerreiro(int vida, int mana, const std::string& nome, int dano, int critico=50) : Personagem(vida, mana, nome)
    {set_dano_arma(dano); set_critico(critico);}

    [[nodiscard]] int dano_arma() const { return dano_arma_; }
    [[nodiscard]] int critico() const { return critico_; }

    void set_dano_arma(int dano){
        if(dano <= 0) { dano_arma_ = 10; }
        else{ dano_arma_ = dano; }
    }

    void set_critico(int critico){
        if(critico <= 0) { critico_ = 10; }
        else{ critico_ = critico; }
    }

    int DanoCritico(int dano, int critico) const override{
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> dist(1, 100);

        int rolagem = dist(gen);
        if(rolagem <= critico) {return dano * 2;}
        return dano;
    }

    int habilidadeOfensiva(int consulta) override{
        if(consulta == 1){ return dano_arma(); }
        return DanoCritico(dano_arma(), critico());
    }

    int habilidadeDefensiva(int consulta) override{
        if(consulta == 1){ return 10; }

        if(mana_ >= 20){
            mana_ -= 20;
            vida_ += 10;
            critico_ += 10;
            return 10;
        }
        return 0;
    }
};

class Inimigo final : public Personagem{
    int dano_;
public:
    Inimigo(int vida, int mana, const std::string& nome, int dano) : Personagem(vida, mana, nome)
    {}

    void set_dano(int dano){
        if(dano <= 0) { dano_ = 10; }
        else{ dano_ = dano; }
    }

    [[nodiscard]] int dano() const { return dano_; }

    int habilidadeOfensiva(int consulta) override{
        if(consulta == 1) { return dano(); }
        return dano();
    }

    int habilidadeDefensiva(int consulta) override{
        if(consulta == 1) { return 5; }
        if(mana_ >= 20){
            mana_ -= 20;
            dano_ += 10;
            vida_ += 5;
            return 5;
        }
        return 0;
    }
};