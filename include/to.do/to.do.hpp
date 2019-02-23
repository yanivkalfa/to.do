#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using std::string;

class [[eosio::contract("to.do")]] to_do : public contract {

public:
    using contract::contract;

    to_do( name receiver, name code, datastream<const char*> ds ): contract(receiver, code, ds) {}

    [[eosio::action]]
    void addtodo(checksum256 id, string name );

    [[eosio::action]]
    void updatetodo( checksum256 id, string name, bool done );

    [[eosio::action]]
    void removetodo( checksum256 id );

private:
    struct [[eosio::table]] todo {
        uint64_t    key;
        checksum256 id;
        string      name;
        bool        done;

        uint64_t primary_key() const { return key; }
        checksum256 by_todoid() const { return id; }
    };

    typedef multi_index<"todos"_n, todo,
        indexed_by<"todoid"_n, const_mem_fun<todo, checksum256, &todo::by_todoid>>
    > todo_list;
};