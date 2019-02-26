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
    auto todostable_by_id = todostable.get_index<"todoid"_n>();
    auto iterator = todostable_by_id.find(id);
    eosio_assert(iterator == todostable_by_id.end(), "Todo with this id exists");

    todostable.emplace( _self, [&]( auto& row ) {
        row.key   = todostable.available_primary_key();
        row.id              = id;
        row.name            = name;
        row.done            = false;
    });

    print( "todo added, ", id);
}

void to_do::updatetodo( checksum256 id, string name, bool done )
{
    todo_list todostable(_self, _self.value);
    auto todostable_by_id = todostable.get_index<"todoid"_n>();
    auto iterator = todostable_by_id.find(id);
    eosio_assert(iterator != todostable_by_id.end(), "Todo with this id doesnt exist");

    todostable_by_id.modify(iterator, _self, [&]( auto& row ) {
        row.name    = name;
        row.done    = done;
    });

    print( "todo updated, ", id);
}

void to_do::removetodo( checksum256 id )
{
    todo_list todostable(_self, _self.value);
    auto todostable_by_id = todostable.get_index<"todoid"_n>();
    auto iterator = todostable_by_id.find(id);
    eosio_assert(iterator != todostable_by_id.end(), "Todo with this id doesnt exist");
    todostable_by_id.erase(iterator);

    print( "todo delete, ", id);
}

void to_do::truncatetable()
{
    todo_list todostable(_self, _self.value);
    for(auto& item : todostable) {
        auto iterator = todostable.find(item.key);
        if( iterator != todostable.end() ) {
            todostable.erase(iterator);
        }
    }
}

EOSIO_DISPATCH( to_do, (addtodo)(updatetodo)(removetodo)(truncatetable))
