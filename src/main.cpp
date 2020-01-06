#include <stdio.h>
#include <cstdarg>
#include "Core/Memory/Arena.h"
#include "Core/Import/Fbx_Parse.h"

const char* indent_buffer = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
FILE* dump_file = NULL;
u32 current_indent = 0;
char last_dump_char = '\n';

void dump_indent()
{
	fwrite(indent_buffer, current_indent, 1, dump_file);
}
void dump(const char* format, ...)
{
	va_list vl;
	va_start(vl, format);
	u32 str_len = vsnprintf(NULL, 0, format, vl);
	char* buffer = new char[str_len + 1];
	vsprintf(buffer, format, vl);


	for(u32 i=0; i<str_len; ++i)
	{
		if (last_dump_char == '\n')
			dump_indent();

		fwrite(buffer + i, 1, 1, dump_file);
		last_dump_char = buffer[i];
	}

	delete buffer;
}

const char* get_property_type_str(Fbx_Property_Type type)
{
	switch(type)
	{
		case Fbx_Property_Type::Bool: return "(Bool)";
		case Fbx_Property_Type::Short: return "(Short)";
		case Fbx_Property_Type::Int: return "(Int)";
		case Fbx_Property_Type::Long: return "(Long)";
		case Fbx_Property_Type::Float: return "(Float)";
		case Fbx_Property_Type::Double: return "(Double)";

		case Fbx_Property_Type::Bool_Array: return "(Bool[])";
		case Fbx_Property_Type::Int_Array: return "(Int[])";
		case Fbx_Property_Type::Long_Array: return "(Long[])";
		case Fbx_Property_Type::Float_Array: return "(Float[])";
		case Fbx_Property_Type::Double_Array: return "(Double[])";

		case Fbx_Property_Type::String: return "(String)";
		case Fbx_Property_Type::Raw: return "(Raw)";
	}

	return "(UNKNOWN)";
}

#define PROP_GET(ptr, type) (*((type*)ptr))
#define PROP_ARRAY_GET(ptr, type, index) (((type*)ptr)[index])

void dump_property(Fbx_Property* prop)
{
	void* data = prop->data;
	Fbx_Property_Type type = prop->type;
	
	dump("%s ", get_property_type_str(type));

	// Lower-case, array
	if ((i8)type >= 'a')
	{
		Fbx_Array* array = (Fbx_Array*)data;
		current_indent++;
		for(u32 i=0; i<array->length; ++i)
		{
			switch(type)
			{
				case Fbx_Property_Type::Bool_Array:
					dump("%s, ", PROP_ARRAY_GET(array->data, i8, i) ? "True" : "False");
					break;

				case Fbx_Property_Type::Int_Array:
					dump("%d, ", PROP_ARRAY_GET(array->data, i32, i));
					break;

				case Fbx_Property_Type::Long_Array:
					dump("%lld, ", PROP_ARRAY_GET(array->data, i64, i));
					break;

				case Fbx_Property_Type::Float_Array:
					dump("%f, ", PROP_ARRAY_GET(array->data, float, i));
					break;

				case Fbx_Property_Type::Double_Array:
					dump("%f, ", PROP_ARRAY_GET(array->data, double, i));
					break;
			}
		}
		current_indent--;
	}
	else
	{
		switch(type)
		{
			case Fbx_Property_Type::Bool:
				dump("%s", PROP_GET(data, i8) ? "True" : "False");
				break;
			case Fbx_Property_Type::Short:
				dump("%hu", PROP_GET(data, i16));
				break;
			case Fbx_Property_Type::Int:
				dump("%hu", PROP_GET(data, i32));
				break;
			case Fbx_Property_Type::Long:
				dump("%llu", PROP_GET(data, i64));
				break;

			case Fbx_Property_Type::Float:
				dump("%f", PROP_GET(data, float));
				break;
			case Fbx_Property_Type::Double:
				dump("%f", PROP_GET(data, double));
				break;

			case Fbx_Property_Type::String:
				Fbx_String* string = (Fbx_String*)data;
				dump("'%.*s'", string->length, string->data);
				break;
		}
	}
}

void dump_node(Fbx_Node* node)
{
	dump("'%.*s':\n", node->name_len, node->name);
	dump("{\n");
	current_indent++;

	if (node->property_count > 0)
	{
		for(u32 i=0; i<node->property_count; ++i)
		{
			dump_property(node->properties + i);
			dump("\n");
		}

		if (node->child)
			dump("\n");
	}

	if (node->child)
		dump_node(node->child);

	current_indent--;
	dump("}\n");

	if (node->next)
		dump_node(node->next);
}

int main(int num_args, char** arg_list)
{
	if (num_args != 2)
	{
		printf("Usage: fbxdump filename");
		return 1;
	}

	const char* path = arg_list[1];
	Mem_Arena arena;
	arena_init(&arena);

	Fbx_Node* root = fbx_parse_node_tree(path, &arena);
	if (root == nullptr)
		return 1;

	u32 src_len = strlen(path);
	char* dest_path = new char[src_len + 6];
	memcpy(dest_path, path, src_len);
	memcpy(dest_path + src_len, ".dump", 6);

	// Open dump file to write
	dump_file = fopen(dest_path, "w");
	dump_node(root->child);

	return 0;
}