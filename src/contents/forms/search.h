/**
 * Tatoeba Project, free collaborative creation of multilingual corpuses project
 * Copyright (C) 2011 Allan SIMON <allan.simon@supinfo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @category Tatoebacpp
 * @package  Forms
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#ifndef TATOEBA_SEARCH_FORM_H
#define TATOEBA_SEARCH_FORM_H

#include <cppcms/form.h>
#include "generics/Languages.h"

namespace forms {

    /**
     * @struct SearchesSimple
     * form that permit to search for sentences
     */
    struct SearchesSimple : public cppcms::form {
        /**
         * Query to send to the search engine
         */
        cppcms::widgets::text query;

        /**
         * Language in which we want the results
         */
        cppcms::widgets::select sentencesLang;
        
        
        /**
         * Language in which we want the results to 
         * have translations in
         */
        cppcms::widgets::select translatedInLang;

        /**
         * HTML submit button
         */
        cppcms::widgets::submit submit;
        
        
        SearchesSimple() {
            add(query);
            add(sentencesLang);
            add(translatedInLang);
            add(submit);

            query.name("query");

            //TODO replace und by mul
            sentencesLang.add("Any","und");
            translatedInLang.add("Any","und");


            submit.name("search");
            submit.value("Search");

            query.non_empty();
            // TODO for select I'm sure there's something more specific for
            // selects to say "value must one the possible values of the select"
            sentencesLang.non_empty();
            translatedInLang.non_empty();
        };



        /**
         * Test if the form is correctly filled
         */
        virtual bool validate() {
            if (!form::validate()) {
                return false;
            }
            return true;
        }

        void set_langs() {
            NameToISOMap nameToIso = Languages::get_instance()->get_name_to_iso_map();
            NameToISOMap::const_iterator itr;
            for(itr = nameToIso.begin(); itr != nameToIso.end(); ++itr){
                sentencesLang.add(itr->first,itr->second);
                translatedInLang.add(itr->first,itr->second);
            }

        }

        void set_langs(
            const std::vector<std::string> &userLangs
        ) {
            if (!userLangs.empty()) {
                // we iterate over the user vector and call
                // get_name_from_iso rather iterating over the map
                // because usually the user vector is very short (around
                // 3~5 elements against 100 elements for the map
                // and more in the future
                std::vector<std::string>::const_iterator itr;
                for(itr = userLangs.begin(); itr != userLangs.end(); ++itr){
                    const std::string &iso = *itr;
                    const std::string name = Languages::get_instance()->get_name_from_iso(
                        iso
                    );
                    sentencesLang.add(name, iso);
                    translatedInLang.add(name, iso);
                }
            } else {

                set_langs();
            }

        }
        
    };

}
#endif

