#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <memory.h>
#include <string.h>
#include <json.hpp>
using namespace io;
using namespace json;
void indent(int spaces, FILE* file) {
    while(spaces--) fprintf(file,"    ");
}
// accept any reader regardless of capture size
void dump(json_reader_base& reader, FILE* file) {
    // don't de-escape and dequote field names or string values:
    //reader.raw_strings(true);
    
    bool first_part=true; // first value part in series
    int tabs = 0; // number of "tabs" to indent by
    bool skip_read = false; // don't call read() the next iteration
    while(skip_read || reader.read()) {
        skip_read = false;
        switch(reader.node_type()) {
            case json_node_type::array:
                indent(tabs++,file);
                fputs("[",file);
                break;
            case json_node_type::end_array:
                indent(--tabs,file);
                fputs("]",file);
                break;
            case json_node_type::object:
                indent(tabs++,file);
                fputs("{",file);
                break;
            case json_node_type::end_object:
                indent(--tabs,file);
                fputs("}",file);
                break;
            case json_node_type::field:
                indent(tabs,file);
                fprintf(file, "%s: ",reader.value());
                // we want to spit the value here, so 
                // we basically hijack the reader and 
                // read the value subtree here.
                while(reader.read() && reader.is_value()) {
                    fprintf(file,"%s",reader.value());
                }
                fputs("",file);
                skip_read = true;
                break;
            case json_node_type::value:
                indent(tabs,file);
                fprintf(file,"%s\r\n",reader.value());
                //fwrite(reader.value(),1,strlen(reader.value()),file);
                fputs("",file);
                break;
            case json_node_type::value_part:
                // the first value part needs to be indented
                if(first_part) {
                    indent(tabs,file);
                    first_part = false; // reset the flag
                }
                fprintf(file,"%s",reader.value());
                break;
            case json_node_type::end_value_part:
                fprintf(file,"%s,\r\n",reader.value());               
                // set the first flag
                first_part = true;
                break;      
        }
    }
}

int main() {
    file_stream stm("..\\..\\data.json",io::file_mode::read);
    json_reader reader(stm);
    dump(reader,stdout);
    return 0;
}