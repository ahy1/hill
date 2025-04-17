#ifndef ANALYZER_HPP_INCLUDED
#define ANALYZER_HPP_INCLUDED

#include "lang_spec.hpp"
#include "lexer.hpp"
#include "type.hpp"
#include "type_conversion.hpp"
#include "instr.hpp"


#include <cstdlib>
#include <memory>
#include <stack>
#include <iostream>
#include <map>
#include <vector>
#include <cstdint>

namespace hill
{
	struct frame { // Actual data storage
		std::vector<std::uint64_t> data;
	};

	struct val { // Data ref
		frame *frame;
		size_t ix;
	};

	struct scope { // The names and values
		std::map<std::string, val> ids;
		frame frame;
	};

	struct block { // The code
		scope scope;
		std::vector<instr> instrs;

		void add(const token &t)
		{
			auto instr = make_instr(t);

			switch (t.get_actual_arity()) {
			case tt_arity::NULLARY: throw not_implemented_exception();
			case tt_arity::LUNARY: throw not_implemented_exception();
			case tt_arity::RUNARY: throw not_implemented_exception();
			case tt_arity::BINARY:
				if (instrs.size()<2) throw semantic_error_exception();
				size_t left_ix = instrs.size()-2;
				size_t right_ix = instrs.size()-1;
				const auto &res_type = convert_binary(
					t.get_type(),
					instrs[left_ix].get_type(),
					instrs[right_ix].get_type());
				if (is_type<id>(instrs[left_ix].get_type())) {
					//auto name = dynamic_cast<id &>(instrs[left_ix]).name;
					//scope[instrs[left_ix]
				} else throw semantic_error_exception();
				/*instrs[left_ix].set_type(res_type);
				instr.set_type(res_type);*/
				// TODO: Register id in scope (if not already there)
				// TODO: Set actual type of operator expression
				break;
			}

			instrs.push_back(instr);
		}
	};

	struct analyzer {
		analyzer() {
		}

		block main;

		void analyze_token(const token &t)
		{
			std::cout<<"analyzer: "<< t.str() <<'\n';

			main.add(t);

		}
	};

}

#endif