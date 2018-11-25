产生式关系图
===============================

Declaration
-----------------

.. graphviz::

    digraph declaration {
        overlap=false;
        rankdir=RL;
        compound=true;
        splines=ortho;
        nodesep = 0.1;
        ranksep = 0.05;
        node [shape=point,style=filled, width=0, height=0, margin=0, fillcolor="#fafafa", color="#cccccc", fontcolor="#333333"];
        edge [arrowhead=none, color="#999999"];
        graph [style=filled, fillcolor="#f8f8f8", color="#cccccc"];
        declaration [shape=box, margin="0.1, 0.05"];
        decprod
        [
            shape = none
            label = <<table border="0" cellspacing="0">
                    <tr><td port="port1" border="1">declaration-specifiers</td></tr>
                    <tr><td port="port2" border="1" bgcolor="#dddddd">init-declarator-list</td></tr>
                    <tr><td port="port3" border="1" bgcolor="#eefbee"><font color="#226828">;</font></td></tr>
                    </table>>
        ]
        subgraph cluster_declaration_specifier {
        "declaration-specifiers"
        [
            shape = none,
            label = <<table border="0" cellspacing="0">
                    <tr><td port="port1" border="1" width="141">storage-class-specifier</td></tr>
                    <tr><td port="port2" border="1" bgcolor="#dddddd"><font color="#8888c8">declaration-specifiers</font></td></tr>
                    </table>>
        ];
        "declaration-specifiers1"
        [
            shape = none,
            label = <<table border="0" cellspacing="0">
                    <tr><td port="port1" border="1" width="141">type-specifier</td></tr>
                    <tr><td port="port2" border="1" bgcolor="#dddddd"><font color="#8888c8">declaration-specifiers</font></td></tr>
                    </table>>
        ];
        "declaration-specifiers2"
        [
            shape = none
            label = <<table border="0" cellspacing="0">
                    <tr><td port="port1" border="1" width="141">type-qualifier</td></tr>
                    <tr><td port="port2" border="1" bgcolor="#dddddd"><font color="#8888C8">declaration-specifiers</font></td></tr>
                    </table>>
        ];}

        subgraph cluster_storage {
            auto [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">auto</font></td></tr></table>>];
            register [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">register</font></td></tr></table>>];
            static [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">static</font></td></tr></table>>];
            extern [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">extern</font></td></tr></table>>];
            typedef [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">typedef</font></td></tr></table>>];
        }

        subgraph cluster_type_spec {
            void [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">void</font></td></tr></table>>];
            char [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">char</font></td></tr></table>>];
            short [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">short</font></td></tr></table>>];
            int [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">int</font></td></tr></table>>];
            long [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">long</font></td></tr></table>>];
            float [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">float</font></td></tr></table>>];
            double [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">double</font></td></tr></table>>];
            signed [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">signed</font></td></tr></table>>];
            unsigned [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">unsigned</font></td></tr></table>>];
            "struct-or-union-specifier-o" [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" width="141">struct-or-union-specifier</td></tr></table>>];
            "enum-specifier-o" [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" width="141">enum-specifier</td></tr></table>>];
            "typedef-name-o" [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" width="141">typedef-name</td></tr></table>>];
        }

        subgraph cluster_type_qualifier {
            const [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">const</font></td></tr></table>>];
            volatile [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">volatile</font></td></tr></table>>];
        }


        "struct-or-union-specifier"
        [
            shape = none,
            label = <<table border="0" cellspacing="0">
                    <tr><td port="port1" border="1" width="141">struct-or-union</td></tr>
                    <tr><td port="port2" border="1" bgcolor="#fcf4f5"><font color="#68202a">identifier</font></td></tr>
                    <tr><td port="port3" border="1" bgcolor="#eefbee"><font color="#226828">{</font></td></tr>
                    <tr><td port="port4" border="1">struct-declaration-list</td></tr>
                    <tr><td port="port5" border="1" bgcolor="#eefbee"><font color="#226828">}</font></td></tr>
                    </table>>
        ];

        subgraph cluster_struct_or_union {
            struct [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">struct</font></td></tr></table>>];
            union [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">union</font></td></tr></table>>];
        }

        "struct-declaration-list"
        [
            shape = none,
            label = <<table border="0" cellspacing="0">
                    <tr><td port="port1" border="1" bgcolor="#dddddd" width="141"><font color="#8888c8">struct-declaration-list</font></td></tr>
                    <tr><td port="port2" border="1" >struct-declaration</td></tr>
                    </table>>
        ];
        subgraph cluster_struct_declaration {
            "struct-declaration"
            [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">struct-declarator-list</td></tr>
                        <tr><td port="port2" border="1"  >specifier-qualifier-list</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#eefbee"><font color="#226828">;</font></td></tr>
                        </table>>
            ]
        }
        subgraph cluster_struct_declarator_list {
            "struct-declarator" [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" width="141">struct-declarator</td></tr></table>>];
            struct_list_and
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141"><font color="#8888c8">struct-declarator-list</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee"><font color="#226828">,</font></td></tr>
                        <tr><td port="port3" border="1">struct-declarator</td></tr>
                        </table>>];
        }
        "specifier-qualifier-list"
        [
            shape = none,
            label = <<table border="0" cellspacing="0">
                    <tr><td port="port1" border="1"  >type-specifier</td></tr>
                    <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#8888c8">specifier-qualifier-list</font></td></tr>
                    </table>>
        ]

        subgraph cluster_init_declarator_list {
            "init-declarator-list"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141"><font color="#8888c8">init-declarator-list</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee"><font color="#226828">,</font></td></tr>
                        <tr><td port="port3" border="1">init-declarator</td></tr>
                        </table>>];
        }

        subgraph cluster_init_declarator {
            "init-declarator"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">declarator</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd"><font color="#226828">=</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd">initializer</td></tr>
                        </table>>];
        }

        subgraph cluster_enum_specifier {
            "enum-specifier"[shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">enum</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#fcf4f5"><font color="#68202a">identifier</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#eefbee"><font color="#226828">{</font></td></tr>
                        <tr><td port="port4" border="1">enumerator-list</td></tr>
                        <tr><td port="port5" border="1" bgcolor="#eefbee"><font color="#226828">}</font></td></tr>
                        </table>>];
            "enum-specifier1"
            [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">enum</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee"><font color="#226828">{</font></td></tr>
                        <tr><td port="port3" border="1">enumerator</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee"><font color="#226828">}</font></td></tr>
                        </table>>
            ];
            "enum-specifier2"
            [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">enum</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#fcf4f5"><font color="#68202a">identifier</font></td></tr>
                        </table>>
            ];
        }

        subgraph cluster_enumerator_list {
            "enumerator-list" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd"><font color="#226828">enumerator-list</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">,</font></td></tr>
                        <tr><td port="port3" border="1">enumerator</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_enumerator {
            enumerator [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1">identifier</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd"><font color="#226828">=</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141"><font color="#226828">constant-expression</font></td></tr>
                        </table>>
            ]
        }

        "typedef-name"
        [
            shape = none,
            label = <<table border="0" cellspacing="0">
                    <tr><td port="port2" border="1" bgcolor="#fcf4f5" width="141"><font color="#68202a">identifier</font></td></tr>
                    </table>>
        ]

        subgraph cluster_struct_declarator {
            declarator [shape=none, label=<<table border="0" cellspacing="0" width="141"><tr ><td port="port1" border="1" width="141">declarator</td></tr></table>>];
            declarator_colon
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">declarator</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee"><font color="#226828">:</font></td></tr>
                        <tr><td port="port4" border="1">constant-expression</td></tr>
                        </table>>];
        }
        subgraph cluster_declarator {
            "pointer direct-declarator"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">pointer</td></tr>
                        <tr><td port="port2" border="1" >direct-declarator</td></tr>
                        </table>>];
        }
        subgraph cluster_pointer {
            "*"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">*</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd">type-qualifier-list</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd">pointer</td></tr>
                        </table>>];
        }
        subgraph cluster_direct_declarator {
            "direct-declarator1"[shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port1" border="1" width="141">identifier</td></tr></table>>];
            "direct-declarator2"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port2" border="1" >declarator</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        </table>>];
            "direct-declarator3"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" >direct-declarator</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">'['</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd">constant-expression </td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">']'</font></td></tr>
                        </table>>];
            "direct-declarator4"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" >direct-declarator</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd">parameter-type-list</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        </table>>];
            "direct-declarator5"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" >direct-declarator</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd">identifier-list</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        </table>>];
        }

        subgraph cluster_initializer {
            initializer1 [
                shape = none,
                label = <<table border="0" cellspacing="0">
                    <tr><td port="port1" border="1" width="141">assignment-expression</td></tr>
                    </table>>
            ]
            initializer2 [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">{</font></td></tr>
                        <tr><td port="port2" border="1" width="141">initializer-list</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141"><font color="#226828">,</font></td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">}</font></td></tr>
                        </table>>
            ]
        }

        subgraph cluster_initializer_list {
            "initializer-list" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd">initializer-list</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd"><font color="#226828">,</font></td></tr>
                        <tr><td port="port3" border="1" width="141">initializer</td></tr>
                    </table>>
            ]
        }

        subgraph cluster_parameter_type_list {
            "parameter-type-list" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">parameter-list</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd"><font color="#226828">,</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd"><font color="#226828">...</font></td></tr>
                    </table>>
            ]
        }

        subgraph cluster_parameter_list {
            "parameter-list" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd">parameter-list</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd"><font color="#226828">,</font></td></tr>
                        <tr><td port="port3" border="1" width="141">parameter-declaration</td></tr>
                    </table>>
            ]
        }

        subgraph cluster_parameter_declaration {
            "declaration-specifiers declarator" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">declaration-specifiers</td></tr>
                        <tr><td port="port1" border="1" width="141">declarator</td></tr>
                    </table>>
            ]
            "declaration-specifiers abstruct-declarator" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">declaration-specifiers</td></tr>
                        <tr><td port="port1" border="1" width="141">abstruct-declarator</td></tr>
                    </table>>
            ]
            "declaration-specifiers -" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">declaration-specifiers</td></tr>
                    </table>>
            ]
        }

        subgraph cluster_abstruct_declarator {
            "abstruct-declarator" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd">pointer</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd">direct-abstruct-declarator</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_direct_abstruct_declarator {
            "(abstruct-declarator)" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141">abstruct-declarator</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        </table>>
            ]
            "direct-abstruct-declarator[]" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">direct-abstruct-declarator</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">'['</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141">constant-expression</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">']'</font></td></tr>
                        </table>>
            ]
            "direct-abstruct-declarator()" [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">direct-abstruct-declarator</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141">parameter-type-list</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        </table>>
            ]
        }

        declaration -> decprod;
        decprod:port1 -> point1 -> "declaration-specifiers"[lhead=cluster_declaration_specifier];
        decprod:port2 -> pointt1 -> "init-declarator-list" [lhead=cluster_init_declarator_list];
        "declaration-specifiers":port1 -> point2 -> auto [lhead=cluster_storage, ltail=cluster_declaration_specifier];
        "declaration-specifiers1":port1 -> point3 -> void [lhead=cluster_type_spec, ltail=cluster_declaration_specifier ];

        "declaration-specifiers2":port1 -> point4 -> const [lhead=cluster_type_qualifier, ltail=cluster_declaration_specifier];
        "init-declarator-list":port3 -> pt2 -> "init-declarator" [lhead=cluster_init_declarator, ltail=cluster_init_declarator_list];
        "struct-or-union-specifier-o" -> point10 -> "struct-or-union-specifier" [ltail=cluster_type_spec];
        "struct-or-union-specifier":port1 -> point6 -> struct [ltail=cluster_struct_or_union];
        "struct-or-union-specifier":port4 -> point7 -> "struct-declaration-list";
        "struct-declaration-list":"port2" -> point8 -> "struct-declaration"[lhead=cluster_struct_declaration];
        {rank = same; point10; point11; point12;}
        {rank = same; "struct-or-union-specifier"; "typedef-name"; cluster_enum_specifier;};
        "enum-specifier-o" -> point11 -> "enum-specifier" [ltail=cluster_type_spec,lhead=cluster_enum_specifier];
        "typedef-name-o" -> point12 -> "typedef-name" [ltail=cluster_type_spec];
        "struct-declaration":"port1" -> point9 -> "struct-declarator" [lhead=cluster_struct_declarator_list,ltail=cluster_struct_declaration];
        "struct-declaration":"port2" -> point13 -> "specifier-qualifier-list" [ltail=cluster_struct_declaration];
        {rank = same; point9; point13;}
        "enum-specifier":port4 -> point14 -> "enumerator-list" [lhead=cluster_enumerator_list];
        "enum-specifier1":port3 -> point15 -> "enumerator" [lhead=cluster_enumerator];
        "struct-declarator" -> declarator [lhead=cluster_struct_declarator, ltail=cluster_struct_declarator_list];
        "init-declarator":port1 -> pt11 -> "pointer direct-declarator"[lhead=cluster_declarator, ltail=cluster_init_declarator];
        "init-declarator":port3 -> pt14 -> initializer1 [lhead=cluster_declarator, ltail=cluster_init_declarator];
        "pointer direct-declarator":port1 -> pt12 -> "*" [lhead=cluster_pointer, ltail=cluster_declarator];
        "pointer direct-declarator":port2 -> pt13 -> "direct-declarator1" [lhead=cluster_direct_declarator, ltail=cluster_declarator];
        initializer2:port2 -> pt15 -> "initializer-list"[lhead=cluster_initializer_list, ltail=cluster_initializer];
        "direct-declarator4":port3 -> pt16 -> "parameter-type-list" [lhead=cluster_parameter_list];
        "parameter-type-list":port1 -> pt17 -> "parameter-list" [lhead=cluster_parameter_list];
        "parameter-list":port3 -> "declaration-specifiers declarator" [lhead=cluster_parameter_declaration];
        "abstruct-declarator"  -> "declaration-specifiers abstruct-declarator":port2 [lhead=cluster_parameter_declaration];
        "(abstruct-declarator)" -> pt18 -> "abstruct-declarator" [lhead=cluster_direct_abstruct_declarator];

    }



Function-definition
------------------------

.. graphviz::

    digraph function {
        overlap=false;
        rankdir=RL;
        compound=true;
        splines=ortho;
        nodesep = 0.1;
        ranksep = 0.05;
        node [shape=point,style=filled, width=0, height=0, margin=0, fillcolor="#fafafa", color="#cccccc", fontcolor="#333333"];
        edge [arrowhead=none, color="#999999"];
        graph [style=filled, fillcolor="#f8f8f8", color="#cccccc"];
        "function-definition" [shape=box, margin="0.1, 0.05"];

        subgraph cluster_function_definition {
            "func-definition"
            [shape = none, label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">declaration-specifiers</td></tr>
                        <tr><td port="port2" border="1">declarator</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141">declaration-list</td></tr>
                        <tr><td port="port4" border="1">compound-statement</td></tr>
                        </table>>];
        }

        subgraph cluster_compound_statement {
            "compound-statement"
            [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">{</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141">declaration-list</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141">statement-list</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">}</font></td></tr>
                        </table>>
            ];

        }

        subgraph cluster_statement_list {
            "statement-list"
            [
                shape = none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">statement-list</td></tr>
                        <tr><td port="port2" border="1" width="141">statement</td></tr>
                        </table>>
            ];

        }

        subgraph cluster_statement {
            "labeled-statement-" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141">labeled-statement</td></tr></table>>];
            "expression-statement-" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141">expression-statement</td></tr></table>>];
            "compound-statement-" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141">compound-statement</td></tr></table>>];
            "selection-statement-" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141">selection-statement</td></tr></table>>];
            "iteration-statement-" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141">iteration-statement</td></tr></table>>];
            "jump-statement-" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141">jump-statement</td></tr></table>>];

        }

        subgraph cluster_labeled_statement {
            "labeled-statement1" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">identifier</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">:</font></td></tr>
                        <tr><td port="port3" border="1" width="141">statement</td></tr>
                        </table>>
            ]
            "labeled-statement2" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">case</font></td></tr>
                        <tr><td port="port2" border="1" width="141">constant-expression</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#eefbee" width="141"><font color="#226828">:</font></td></tr>
                        <tr><td port="port4" border="1" width="141">statement</td></tr>
                        </table>>
            ]
            "labeled-statement3" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">default</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">:</font></td></tr>
                        <tr><td port="port3" border="1" width="141">statement</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_expression_statement {
            "expression-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">;</font></td></tr>
                        </table>>
            ]
        }

        subgraph cluster_selection_statement {
            "if-else-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">if</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" width="141">expression</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        <tr><td port="port5" border="1" width="141">statement</td></tr>
                        <tr><td port="port6" border="1" bgcolor="#dddddd" width="141"><font color="#226828">else</font></td></tr>
                        <tr><td port="port7" border="1" bgcolor="#dddddd" width="141">statement</td></tr>
                        </table>>
            ]
            "switch-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">switch</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" width="141">expression</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        <tr><td port="port5" border="1" width="141">statement</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_iteration_statement {
            "while-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">while</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" width="141">expression</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        <tr><td port="port5" border="1" width="141">statement</td></tr>
                        </table>>
            ]
            "do-while-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">do</font></td></tr>
                        <tr><td port="port2" border="1" width="141">statement</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#eefbee" width="141"><font color="#226828">while</font></td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port5" border="1" width="141">expression</td></tr>
                        <tr><td port="port6" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        </table>>
            ]
            "for-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">for</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" width="141">expression</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#eefbee" width="141"><font color="#226828">;</font></td></tr>
                        <tr><td port="port5" border="1" width="141">expression</td></tr>
                        <tr><td port="port6" border="1" bgcolor="#eefbee" width="141"><font color="#226828">;</font></td></tr>
                        <tr><td port="port7" border="1" width="141">expression</td></tr>
                        <tr><td port="port8" border="1" bgcolor="#eefbee" width="141"><font color="#226828">)</font></td></tr>
                        <tr><td port="port9" border="1" width="141">statement</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_jump_statement {
            "goto-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">goto</font></td></tr>
                        <tr><td port="port2" border="1" width="141">identifier</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#eefbee" width="141"><font color="#226828">;</font></td></tr>
                        </table>>
            ]
            "continue-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">continue</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">;</font></td></tr>
                        </table>>
            ]
            "break-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">break</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">;</font></td></tr>
                        </table>>
            ]
            "return-statement" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#eefbee" width="141"><font color="#226828">return</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141">expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">;</font></td></tr>
                        </table>>
            ]
        }


        "function-definition" -> "func-definition" [lhead=cluster_function_definition];
        "func-definition":port4:w -> "compound-statement" [lhead=cluster_compound_statement,ltail=cluster_function_definition];
        "compound-statement":port3 -> "statement-list" [lhead=cluster_statement_list];
        "statement-list":port2 -> "labeled-statement-" [lhead=cluster_statement];
        "labeled-statement-" -> "labeled-statement1" [lhead=cluster_labeled_statement];
        "expression-statement-" -> "expression-statement" [lhead=cluster_expression_statement, ltail=cluster_statement];
        "selection-statement-" -> "if-else-statement" [lhead=cluster_selection_statement];
        "iteration-statement-" -> "while-statement" [lhead=cluster_iteration_statement];
        "jump-statement-" -> "goto-statement" [lhead=cluster_jump_statement];
    }


Expression
------------------------

.. graphviz::

    digraph expression {
        overlap=false;
        rankdir=RL;
        compound=true;
        splines=ortho;
        nodesep = 0.1;
        ranksep = 0.05;
        node [shape=point,style=filled, width=0, height=0, margin=0, fillcolor="#fafafa", color="#cccccc", fontcolor="#333333"];
        edge [arrowhead=none, color="#999999"];
        graph [style=filled, fillcolor="#f8f8f8", color="#cccccc"];
        "expression" [shape=box, margin="0.1, 0.05"];

        subgraph cluster_expression {
            "expression-"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">,</font></td></tr>
                        <tr><td port="port3" border="1" width="141">assignment-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_assignment_expression {
            "conditional-expression" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141">conditional-expression</td></tr></table>>];
            "unary-expression assignment-operator assignment-expression"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">unary-expression</td></tr>
                        <tr><td port="port2" border="1" width="141">assignment-operator</td></tr>
                        <tr><td port="port3" border="1" width="141">assignment-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_conditional_expression {
            "conditional-expression-"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">logical-OR-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">?</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141">expression</td></tr>
                        <tr><td port="port4" border="1" bgcolor="#dddddd" width="141"><font color="#226828">:</font></td></tr>
                        <tr><td port="port5" border="1" bgcolor="#dddddd" width="141">conditional-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_assignment_operator{
            "=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port1" border="1" width="141"><font color="#226828">=</font></td></tr></table>>];
            "x=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141"><font color="#226828">*=</font></td></tr></table>>];
            "/=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port3" border="1" width="141"><font color="#226828">/=</font></td></tr></table>>];
            "%=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port4" border="1" width="141"><font color="#226828">%=</font></td></tr></table>>];
            "+=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port5" border="1" width="141"><font color="#226828">+=</font></td></tr></table>>];
            "-=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port6" border="1" width="141"><font color="#226828">-=</font></td></tr></table>>];
            "<<=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port7" border="1" width="141"><font color="#226828">&lt;&lt;=</font></td></tr></table>>];
            ">>=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port8" border="1" width="141"><font color="#226828">&gt;&gt;=</font></td></tr></table>>];
            "&=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port9" border="1" width="141"><font color="#226828">&amp;=</font></td></tr></table>>];
            "^=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port10" border="1" width="141"><font color="#226828">^=</font></td></tr></table>>];
            "b=" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port11" border="1" width="141"><font color="#226828">b=</font></td></tr></table>>];

        }

        subgraph cluster_logical_OR_expression {
            "logical-OR-expression"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">logical-OR-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">||</font></td></tr>
                        <tr><td port="port3" border="1" width="141">logical-AND-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_logical_AND_expression {
            "logical-AND-expression"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">logical-AND-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">&amp;&amp;</font></td></tr>
                        <tr><td port="port3" border="1" width="141">inclusive-OR-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_inclusive_OR_expression {
            "exclusive-OR-expression"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">inclusive-OR-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#eefbee" width="141"><font color="#226828">|</font></td></tr>
                        <tr><td port="port3" border="1" width="141">exclusive-OR-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_exclusive_OR_expression {
            "exclusive-OR-expression-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">exclusive-OR-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">^</font></td></tr>
                        <tr><td port="port3" border="1" width="141">AND-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_AND_expression {
            "AND-expression-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">AND-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">&amp;</font></td></tr>
                        <tr><td port="port3" border="1" width="141">equality-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_equality_expression {
            "equality-expression-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">equality-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">==  !=</font></td></tr>
                        <tr><td port="port3" border="1" width="141">relational-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_relational_expression {
            "relational-expression-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">relational-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">&lt; &gt; &lt;= &gt;=</font></td></tr>
                        <tr><td port="port3" border="1" width="141">shift-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_shift_expression {
            "shift-expression-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">shift-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">&lt;&lt; &gt;&gt;</font></td></tr>
                        <tr><td port="port3" border="1" width="141">additive-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_additive_expression {
            "additive-expression-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">additive-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">+ -</font></td></tr>
                        <tr><td port="port3" border="1" width="141">multiplicative-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_multiplicative_expression {
            "multiplicative-expression-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">multiplicative-expression</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">* / %</font></td></tr>
                        <tr><td port="port3" border="1" width="141">cast-expression</td></tr>
                        </table>>
            ]
        }


        subgraph cluster_cast_expression {
            "cast-expression-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141">type-name</td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141"><font color="#226828">)</font></td></tr>
                        <tr><td port="port4" border="1" width="141">unary-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_unary_expression {
            "unary-expression-body1"
            [
                shape=none,
            label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">postfix-expression</td></tr>
                        </table>>
            ]
            "unary-expression-body2"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141"><font color="#226828">++ -- sizeof</font></td></tr>
                        <tr><td port="port2" border="1" width="141">unary-expression</td></tr>
                        </table>>
            ]

            "unary-expression-body3"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">unary-operator</td></tr>
                        <tr><td port="port2" border="1" width="141">cast-expression</td></tr>
                        </table>>
            ]

            "unary-expression-body4"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141"><font color="#226828">sizeof</font></td></tr>
                        <tr><td port="port2" border="1" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" width="141">type-name</td></tr>
                        <tr><td port="port4" border="1" width="141"><font color="#226828">)</font></td></tr>
                        </table>>
            ]
        }

        subgraph cluster_unary_operator {
            "&" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port1" border="1" width="141"><font color="#226828">&amp;</font></td></tr></table>>];
            "*" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141"><font color="#226828">*</font></td></tr></table>>];
            "+" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port3" border="1" width="141"><font color="#226828">+</font></td></tr></table>>];
            "-" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port4" border="1" width="141"><font color="#226828">-</font></td></tr></table>>];
            "~" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port5" border="1" width="141"><font color="#226828">~</font></td></tr></table>>];
            "!" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port6" border="1" width="141"><font color="#226828">!</font></td></tr></table>>];
        }

        subgraph cluster_postfix_expression {
            "postfix-expression-1" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">primary-expression</td></tr>
                        </table>>
            ]
            "postfix-expression-2" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">postfix-expression</td></tr>
                        <tr><td port="port2" border="1" width="141"><font color="#226828">'['</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141">expression</td></tr>
                        <tr><td port="port4" border="1" width="141"><font color="#226828">']'</font></td></tr>
                        </table>>
            ]
            "postfix-expression-3" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">postfix-expression</td></tr>
                        <tr><td port="port2" border="1" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141">argument-expression-list</td></tr>
                        <tr><td port="port4" border="1" width="141"><font color="#226828">)</font></td></tr>
                        </table>>
            ]
            "postfix-expression-4" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">postfix-expression</td></tr>
                        <tr><td port="port2" border="1" width="141"><font color="#226828">. -&gt;</font></td></tr>
                        <tr><td port="port3" border="1" bgcolor="#dddddd" width="141">identifier</td></tr>
                        </table>>
            ]
            "postfix-expression-5" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141">postfix-expression</td></tr>
                        <tr><td port="port2" border="1" width="141"><font color="#226828">++ --</font></td></tr>
                        </table>>
            ]
        }

        subgraph cluster_primary_expression {
            "identifier" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port1" border="1" width="141">identifier</td></tr></table>>];
            "constant" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port1" border="1" width="141">constant</td></tr></table>>];
            "string" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port1" border="1" width="141">string</td></tr></table>>];
            "(expr)" [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" width="141"><font color="#226828">(</font></td></tr>
                        <tr><td port="port2" border="1" width="141">expression</td></tr>
                        <tr><td port="port3" border="1" width="141"><font color="#226828">)</font></td></tr>
                        </table>>
            ]
        }

        subgraph cluster_argument_expression_list {
            "argument-expression-list-body"
            [
                shape=none,
                label = <<table border="0" cellspacing="0">
                        <tr><td port="port1" border="1" bgcolor="#dddddd" width="141">argument-expression-list</td></tr>
                        <tr><td port="port2" border="1" bgcolor="#dddddd" width="141"><font color="#226828">,</font></td></tr>
                        <tr><td port="port3" border="1" width="141">argument-expression</td></tr>
                        </table>>
            ]
        }

        subgraph cluster_constant {
            "integer-constant" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port1" border="1" width="141"><font color="#226828">integer-constant</font></td></tr></table>>];
            "character-constant" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port2" border="1" width="141"><font color="#226828">character-constant</font></td></tr></table>>];
            "floating-constant" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port3" border="1" width="141"><font color="#226828">floating-constant</font></td></tr></table>>];
            "enumeration-constant" [shape = none, label = <<table border="0" cellspacing="0"><tr><td port="port4" border="1" width="141"><font color="#226828">enumration-constant</font></td></tr></table>>];
        }

        "expression" -> "expression-" [lhead=cluster_expression];
        "expression-":port3 -> "conditional-expression" [lhead=cluster_assignment_expression];
        "unary-expression assignment-operator assignment-expression":port2:w -> "=" [lhead=cluster_assignment_operator];
        "conditional-expression" -> "conditional-expression-" [lhead=cluster_conditional_expression];
        "conditional-expression-":port1 -> "logical-OR-expression" [lhead=cluster_logical_OR_expression];
        "logical-OR-expression":port3 -> "logical-AND-expression" [lhead=cluster_logical_AND_expression];
        "logical-AND-expression":port3 -> "exclusive-OR-expression" [lhead=cluster_inclusive_OR_expression];
        "exclusive-OR-expression" -> "exclusive-OR-expression-body" [lhead=cluster_exclusive_OR_expression];
        "exclusive-OR-expression-body":port3 -> "AND-expression-body" [lhead=cluster_AND_expression];
        "equality-expression-body" -> "AND-expression-body":port3 [lhead=cluster_AND_expression];
        "relational-expression-body" -> "equality-expression-body":port3  [lhead=cluster_equality_expression];
        "shift-expression-body" -> "relational-expression-body":port3 [lhead=cluster_relational_expression];
        "additive-expression-body" -> "shift-expression-body":port3 [lhead=cluster_shift_expression];
        "additive-expression-body":port3 -> "multiplicative-expression-body" [lhead=cluster_multiplicative_expression];
        "multiplicative-expression-body":port3 -> "cast-expression-body" [lhead=cluster_cast_expression];
        "cast-expression-body":port4 -> "unary-expression-body1" [lhead=cluster_unary_expression,ltail=cluster_cast_expression];
        "unary-expression-body3":port1 -> "&" [lhead=cluster_unary_operator];
        "postfix-expression-1":port4 -> "unary-expression-body1" [lhead=cluster_unary_expression, ltail=cluster_postfix_expression];
        "identifier" -> "postfix-expression-1" [lhead=cluster_postfix_expression,ltail=cluster_primary_expression];
        "argument-expression-list-body" -> "postfix-expression-3":port3 [lhead=cluster_argument_expression_list];
        "integer-constant" -> "constant" [lhead=cluster_primary_expression];
    }