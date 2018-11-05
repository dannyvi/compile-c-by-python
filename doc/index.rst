.. compiie documentation master file, created by
   sphinx-quickstart on Mon Nov  5 07:30:49 2018.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to compiie's documentation!
===================================

.. toctree::
   :maxdepth: 2

   record
   changes

example::

   aabb

.. graphviz::

   digraph idp_modules{
     bgcolor="none";
     margin = .5;
     rankdir = TB;
     fontsize = 10;
     node [margin=0.06 ,width=0, height=0, fontsize=10, shape = "record", fontcolor="black"];
     edge [ color="grey47"];

     doc_index [label="文档"];

     intro [label = "简介"];
     guide [label = "导引"];
     reference [label = "参考"];

     doc_index -> intro;
     doc_index -> guide;
     doc_index -> reference;

     { rank = same; intro; guide; reference; }

     backend [label = "后端"];
     frontend [label = "前端"];
     scraper [label = "爬虫"];
     ci      [label = "持续集成"];
     documentation [label = "文档"];

     guide -> backend;
     guide -> frontend;
     guide -> scraper;
     guide -> ci;
     guide -> documentation;

     { rank = same; backend; frontend; scraper; ci; documentation; }

   }


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
