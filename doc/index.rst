.. compiie documentation master file, created by
   sphinx-quickstart on Mon Nov  5 07:30:49 2018.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to compire's documentation!
===================================

.. toctree::
   :maxdepth: 2

   sdt_conversion
   record
   changes
   ref/index
   ir_documentation
   c_production_globs

Diagram
-------------------

.. graphviz::

   digraph compiler_modules{
     bgcolor="none";
     rankdir = TB;
     ranksep = 0.15;
     fontsize = 28;
     margin = "0.3, 0.5";
     fontcolor = "#333385";
     nodesep = 1.0;
     overlap = false;
     labelloc="t" ;
     label = "Complier Activities";
     node [ fontsize=14,color="#98a3b8", fontcolor="#424278"];
     edge [ color="#cccccc", arrowsize=0.6];

     node [shape=record];
     grammar [shape=record,label="{ <f0>  Grammar  | <f1> Translation  | <f2> Definition  } "];
     lexrule [shape=record,label=" Lex Regex "];

     {rank = same; grammar; lexrule; source;}
     node [shape=ellipse, style=filled, fillcolor="#faf3f3", color=none];
     {rank = same;
      Loader[margin="0.3,0.1", shape=box, style=filled, fontsize=21, fontcolor="#384485", fillcolor ="#d8dfef"];
      Lexer[margin="0.3,0.1", shape=box, style=filled, fontsize=21, fontcolor="#384485", fillcolor ="#d8dfef"];
      }
     grammar -> Loader -> Env -> SDT [weight=1.0];

     {rank = same;
      Env [shape=box, style="rounded,filled",fillcolor="#f9f3e0"];
      syntax_table[shape=box, style=filled,fillcolor="#eaf6ed"];
      symbols[shape=box, style=filled,fillcolor="#eaf6ed"];
      token_stream [shape=box, style=filled, fillcolor="#eaf6ed"];
     }
     {rank = same;
      SDT [margin="0.4,0.1",shape=box, style=filled, fontsize=28, fontcolor="#333385", fillcolor ="#d8dfef"];
      parse [shape=ellipse, style=filled, fillcolor="#faf3f3", color="#faf3f3"];
      }
     SDT -> parse ;
     Loader -> syntax_table;
     syntax_table -> SDT ;
     Loader -> symbols -> SDT;
     rule [shape=box, style="rounded,filled",fillcolor="#f9f3e0"];
     code [shape=box, style="rounded,filled",fillcolor="#f9f3e0"];
     {rank = same; stack -> shift -> ahead [dir=back]; }
     stack [shape=box, style=filled, fillcolor="#eaf6ed"];
     SDT -> stack;
     lexrule -> Lexer -> token_stream -> parse -> ahead -> reduce ;
     reduce -> stack [weight=1.2];
     source -> Lexer;
     reduce -> rule [dir=both];
     parse -> code [weight=0.01];
     stack -> rule ;
     rule -> code ;
     Env -> rule [style=dotted, arrowhead=none, weight=0.01];
     Env -> code [style=dotted, arrowhead=none, weight=0.01];

   }


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
