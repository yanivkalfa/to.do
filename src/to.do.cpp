/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <to.do/to.do.hpp>

using namespace eosio;
using std::string;

void to_do::addtodo( checksum256 id, string name )
{
    todo_list todostable(_self, _self.value);
    auto id_index = todostable.get_index<"todoid"_n>();
    auto iterator = id_index.find(id);
    eosio_assert(iterator == id_index.end(), "Todo with this id exists");

    if ( iterator == id_index.end() ) {
        todostable.emplace( _self, [&]( auto& row ) {
            row.auto_increase   = todostable.available_primary_key();
            row.id              = id;
            row.name            = name;
            row.done            = false;
        });

        print( "todo added, ", id);
    }
}

void to_do::updatetodo( checksum256 id, string name, bool done )
{
    todo_list todostable(_self, _self.value);
    auto id_index = todostable.get_index<"todoid"_n>();
    auto iterator = id_index.find(id);
    eosio_assert(iterator != id_index.end(), "Todo with this id doesnt exist");

    todostable.modify(iterator, _self, [&]( auto& row ) {
        row.name    = name;
        row.done    = done;
    });

    print( "todo updated, ", id);
}

void to_do::removetodo( checksum256 id )
{
    todo_list todostable(_self, _self.value);
    auto id_index = todostable.get_index<"todoid"_n>();
    auto iterator = id_index.find(id);
    eosio_assert(iterator != id_index.end(), "Todo with this id doesnt exist");
    todostable.erase(iterator);

    print( "todo delete, ", id);
}

EOSIO_DISPATCH( to_do, (addtodo)(updatetodo)(removetodo))
