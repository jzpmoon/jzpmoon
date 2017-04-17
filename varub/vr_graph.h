#ifndef VR_GRAPH_H
#define VR_GRAPH_H

typedef struct vr_edge{
  struct vr_vertex* vertex;
  struct vr_edge* next;
  int size;
  void* data[];
} vr_edge;

typedef struct vr_vertex{
  vr_edge* edges;
  struct vr_vertex* next;
  int size;
  void* data[];
} vr_vertex;

typedef struct vr_graph{
  vr_vertex* vertexs;
  int vct;
  int ect;
} vr_graph;

vr_graph* vr_graph_vertexs(vr_graph* graph,int vct,int dsz,...);
int vr_graph_edges(vr_graph* graph,int ect,int dsz,...);

#endif
