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
        uint64_t    auto_increase;
        checksum256 id;
        string      name;
        bool        done;

        uint64_t primary_key() const { return auto_increase; }
        checksum256 by_todoid() const { return id; }
    };

    typedef multi_index<"todos"_n, todo,
        indexed_by<"todoid"_n, const_mem_fun<todo, checksum256, &todo::by_todoid>>
    > todo_list;


    /*
    struct [[eosio::table]] mystruct
    {
        uint64_t     key;
        uint64_t     secondid;
        uint64_t			anotherid;
        std::string  name;
        std::string  account;

        uint64_t primary_key() const { return key; }
        uint64_t by_id() const {return secondid; }
        uint64_t by_anotherid() const {return anotherid; }
    };

    typedef eosio::multi_index<"mystruct"_n, mystruct,
        indexed_by<"secondid"_n, const_mem_fun<mystruct, uint64_t, &mystruct::by_id>>,
        indexed_by<"anotherid"_n, const_mem_fun<mystruct, uint64_t, &mystruct::by_anotherid>>
    > datastore;

    struct [[eosio::table]] poll
    {
        uint64_t      key; // primary key
        uint64_t      pollId; // second key, non-unique, this table will have dup rows for each poll because of option
        std::string   pollName; // name of poll
        uint8_t      pollStatus =0; // staus where 0 = closed, 1 = open, 2 = finished
        std::string  option; // the item you can vote for
        uint32_t    count =0; // the number of votes for each itme -- this to be pulled out to separte table.

        uint64_t primary_key() const { return key; }
        uint64_t by_pollId() const {return pollId; }
    };
    typedef multi_index<"poll"_n, poll,
        indexed_by<"pollid"_n, const_mem_fun<poll, uint64_t, &poll::by_pollId>>
    > pollstable;

    struct [[eosio::table]] pollvotes
    {
        uint64_t     key;
        uint64_t     pollId;
        std::string  pollName; // name of poll
        std::string  account; //this account has voted, use this to make sure noone votes > 1

        uint64_t primary_key() const { return key; }
        uint64_t by_pollId() const {return pollId; }
    };
    typedef multi_index<"pollvotes"_n, pollvotes,
        indexed_by<"pollid"_n, const_mem_fun<pollvotes, uint64_t, &pollvotes::by_pollId>>
    > votes;

    //// local instances of the multi indexes
    pollstable _polls;
    votes _votes;
    */
};