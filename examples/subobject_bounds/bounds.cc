#include <stdio.h>

void print_capability(void *ptr)
{
	unsigned permissions = cheri_permissions_get(ptr);
	printf(
	  "0x%x (valid:%d length: 0x%x 0x%x-0x%x otype:%d "
	  "permissions: %c "
	  "%c%c%c%c%c%c %c%c %c%c%c)\n",
	  cheri_address_get(ptr),
	  cheri_tag_get(ptr),
	  cheri_length_get(ptr),
	  cheri_base_get(ptr),
	  cheri_top_get(ptr),
	  cheri_type_get(ptr),
	  (permissions & CHERI_PERM_GLOBAL) ? 'G' : '-',
	  (permissions & CHERI_PERM_LOAD) ? 'R' : '-',
	  (permissions & CHERI_PERM_STORE) ? 'W' : '-',
	  (permissions & CHERI_PERM_LOAD_STORE_CAP) ? 'c' : '-',
	  (permissions & CHERI_PERM_LOAD_GLOBAL) ? 'g' : '-',
	  (permissions & CHERI_PERM_LOAD_MUTABLE) ? 'm' : '-',
	  (permissions & CHERI_PERM_STORE_LOCAL) ? 'l' : '-',
	  (permissions & CHERI_PERM_SEAL) ? 'S' : '-',
	  (permissions & CHERI_PERM_UNSEAL) ? 'U' : '-',
	  (permissions & CHERI_PERM_USER0) ? '0' : '-');
}

// point_definition#begin
struct  Point
{
	int x, y;
};
// point_definition#end

// point_list#begin
struct IntrusiveLinkedList
{
	IntrusiveLinkedList *next;
};

struct PointList
{
	Point point;
	[[cheri::no_subobject_bounds]] IntrusiveLinkedList list;
};
// point_list#end

// unbounded_point#begin
struct [[cheri::no_subobject_bounds]] UnboundedPoint
{
	int x, y;
};
// unbounded_point#end

void __cheriot_compartment("bounds") entry()
{
	// print_point#begin
	Point p;
	print_capability(&p);
	print_capability(&p.x);
	print_capability(&p.y);
	// print_point#end
	UnboundedPoint up;
	print_capability(&up);
	print_capability(&up.x);
	print_capability(&up.y);
	PointList pl;
	print_capability(&pl);
	print_capability(&pl.point);
	print_capability(&pl.list);
}
