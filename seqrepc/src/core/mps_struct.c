
RWStructOneD rws_atomic = {.write = &write_atomic, .read = &read_atomic};
RWStructOneD rws_binary2b = {.write = &write_binary2b, .read = &read_binary2b};
RWStructOneD rws_binary4b = {.write = &write_binary4b, .read = &read_binary4b};
RWStructOneD rws_dnawalk = {.write = &write_dnawalk, .read = &read_dna_walk};
RWStructOneD rws_eiip = {.write = &write_eiip, .read = &read_eiip};
RWStructOneD rws_imaginary = {.write = &write_imaginary, .read = &read_imaginary};
RWStructOneD rws_integer = {.write = &write_integer, .read = &read_integer};
RWStructOneD rws_molecular_mass = {.write = &write_molecular_mass, .read = &read_molecular_mass};
RWStructOneD rws_paired_numeric = {.write = &write_paired_numeric, .read = &read_paired_numeric};
RWStructOneD rws_real = {.write = &write_real, .read = &read_real};

RWStructManyD rws_cgr = {.write = &write_cgr, .read = &read_cgr};
RWStructManyD rws_icgr = {.write = &write_icgr, .read = &read_icgr};
RWStructManyD rws_liao = {.write = &write_liao, .read = &read_liao};
RWStructManyD rws_tetrahedron = {.write = &write_tetrahedron, .read = &read_tetrahedron};
RWStructManyD rws_voss = {.write = &write_voss, .read = &read_voss};
RWStructManyD rws_zcurve = {.write = &write_zcurve, .read = &read_zcurve};

MpStructOneD atomic_s = {.mp = &atomic, .signature = "atomic", .rws = &rws_atomic};
MpStructOneD binary2b_s = {.mp = &binary_2b, .signature = "binary2b", .rws = &rws_binary2b};
MpStructOneD binary4b_s = {.mp = &binary_4b, .signature = "binary4b", .rws = &rws_binary4b};
MpStructOneD dna_walk_s = {.mp = &dna_walk, .signature = "dna_walk", .rws = &rws_dnawalk};
MpStructOneD eiip_s = {.mp = &eiip, .signature = "eiip", .rws = &rws_eiip};
MpStructOneD imaginary_s = {.mp = &imaginary, .signature = "imaginary", .rws = &rws_imaginary};
MpStructOneD integer_s = {.mp = &integer, .signature = "integer", .rws = &rws_integer};
MpStructOneD molecular_mass_s = {.mp = &molecular_mass, .signature = "molecular_mass", .rws = &rws_molecular_mass};
MpStructOneD paired_numeric_s = {.mp = &paired_numeric, .signature = "paired_numeric", .rws = &rws_paired_numeric};
MpStructOneD real_s = {.mp = &real, .signature = "real", .rws = &rws_real};

MpStructManyD cgr_s = {.mp = &cgr, .signature = "cgr", .rws = &rws_cgr};
MpStructManyD icgr_s = {.mp = &icgr, .signature = "icgr", .rws = &rws_icgr};
MpStructManyD liao_s = {.mp = &liao, .signature = "liao", .rws = &rws_liao};
MpStructManyD tetrahedron_s = {.mp = &tetrahedron, .signature = "tetrahedron", .rws = &rws_tetrahedron};
MpStructManyD voss_s = {.mp = &voss, .signature = "voss", .rws = &rws_voss};
MpStructManyD zcurve_s = {.mp = &zcurve, .signature = "zcurve", .rws = &rws_zcurve};

MpStruct mps[MAPPING_NUM] = 
{
	{.one_d = &atomic_s, .many_d = NULL},
	{.one_d = &binary2b_s, .many_d = NULL},
	{.one_d = &binary4b_s, .many_d = NULL},
	{.one_d = &dna_walk_s, .many_d = NULL},
	{.one_d = &eiip_s, .many_d = NULL},
	{.one_d = &imaginary_s, .many_d = NULL},
	{.one_d = &integer_s, .many_d = NULL},
	{.one_d = &molecular_mass_s, .many_d = NULL},
	{.one_d = &paired_numeric_s, .many_d = NULL},
	{.one_d = &real_s, .many_d = NULL},
	{.many_d = &cgr_s, .one_d = NULL},
	{.many_d = &icgr_s, .one_d = NULL},
	{.many_d = &liao_s, .one_d = NULL},
	{.many_d = &tetrahedron_s, .one_d = NULL},
	{.many_d = &voss_s, .one_d = NULL},
	{.many_d = &zcurve_s, .one_d = NULL}
};
 