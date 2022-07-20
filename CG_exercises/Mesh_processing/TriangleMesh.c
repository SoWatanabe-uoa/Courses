#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <assert.h>
#include <math.h>

#include "TriangleMesh.h"


// Read a triangle mesh stored in a file using the OFF file format
void readOFF(const char* filename, TriangleMesh* tri_mesh)
{
    FILE* f;
    char header[100];
    int num_verts, num_tris, num_edges;
    int i;

    f = fopen(filename, "r");
    assert(f);


    // header (OFF) 
    fscanf(f, "%s\n", header);
    assert(!strcmp(header, "OFF"));


    // number of vertices, number of triangles, number of edges (can be 0)
    fscanf(f, "%d %d %d\n", &num_verts, &num_tris, &num_edges);
    assert(num_verts != 0);
    assert(num_tris != 0);


    // allocate memory
    tri_mesh->_number_vertices = num_verts;
    tri_mesh->_number_triangles = num_tris;
    tri_mesh->_vertices = (Vector3*)malloc(num_verts * sizeof(Vector3));
    tri_mesh->_triangles = (Triple*)malloc(num_tris * sizeof(Triple));

    tri_mesh->_triangle_normals = NULL;
    tri_mesh->_vertex_normals = NULL;

    tri_mesh->_number_adj_vertices = NULL;
    tri_mesh->_adj_vertices = NULL;

    // read the num_verts vertices
    for (i = 0; i < num_verts; i++) {
        float x, y, z;
        fscanf(f, "%f %f %f\n", &x, &y, &z);

        tri_mesh->_vertices[i]._x = x;
        tri_mesh->_vertices[i]._y = y;
        tri_mesh->_vertices[i]._z = z;
    }

    // read the num_tris triangles
    for (i = 0; i < num_tris; i++) {
        int dummy, v0, v1, v2;
        fscanf(f, "%d %d %d %d\n", &dummy, &v0, &v1, &v2);
        assert(dummy == 3); // otherwise it contains polygons with >= 4 verts

        tri_mesh->_triangles[i]._v0 = v0;
        tri_mesh->_triangles[i]._v1 = v1;
        tri_mesh->_triangles[i]._v2 = v2;
    }

    fclose(f);
}


// Compute triangle mesh bounding box
void computeBounds(TriangleMesh* tri_mesh, Vector3* lower_bound, Vector3* upper_bound)
{
    float lower_x = FLT_MAX;
    float lower_y = FLT_MAX;
    float lower_z = FLT_MAX;
    float upper_x = -FLT_MAX;
    float upper_y = -FLT_MAX;
    float upper_z = -FLT_MAX;

    int i;

    for (i = 0; i < tri_mesh->_number_vertices; i++) {
        lower_x = fminf(lower_x, tri_mesh->_vertices[i]._x);
        lower_y = fminf(lower_y, tri_mesh->_vertices[i]._y);
        lower_z = fminf(lower_z, tri_mesh->_vertices[i]._z);

        upper_x = fmaxf(upper_x, tri_mesh->_vertices[i]._x);
        upper_y = fmaxf(upper_y, tri_mesh->_vertices[i]._y);
        upper_z = fmaxf(upper_z, tri_mesh->_vertices[i]._z);
    }

    lower_bound->_x = lower_x;
    lower_bound->_y = lower_y;
    lower_bound->_z = lower_z;

    upper_bound->_x = upper_x;
    upper_bound->_y = upper_y;
    upper_bound->_z = upper_z;
}


// Compute center of mass of the vertices
void computeCenterMass(TriangleMesh* tri_mesh, Vector3* center)
{
    int i;

    center->_x = 0.f;
    center->_y = 0.f;
    center->_z = 0.f;

    for (i = 0; i < tri_mesh->_number_vertices; i++) {
        center->_x += tri_mesh->_vertices[i]._x;
        center->_y += tri_mesh->_vertices[i]._y;
        center->_z += tri_mesh->_vertices[i]._z;
    }

    center->_x /= tri_mesh->_number_vertices;
    center->_y /= tri_mesh->_number_vertices;
    center->_z /= tri_mesh->_number_vertices;
}


// Translate a triangle mesh such that its center of mass is aligned
// with the origin of the coordinate system
void centerTriangleMesh(TriangleMesh* tri_mesh)
{
    int i;

    // compute center of mass
    Vector3 center;
    computeCenterMass(tri_mesh, &center);

    // translate each vertex by -c
    for (i = 0; i < tri_mesh->_number_vertices; i++) {
        tri_mesh->_vertices[i]._x -= center._x;
        tri_mesh->_vertices[i]._y -= center._y;
        tri_mesh->_vertices[i]._z -= center._z;
    }
}


// Rescale a triangle mesh such that it has a bounding
// box with unit length diagonal
void normalizeTriangleMesh(TriangleMesh* tri_mesh)
{
    int i;

    Vector3 lower;
    Vector3 upper;
    Vector3 diagonal;

    float diagonal_length;


    computeBounds(tri_mesh, &lower, &upper);
    sub(upper, lower, &diagonal);
    computeNorm(diagonal, &diagonal_length);

    assert(diagonal_length != 0.f);


    for (i = 0; i < tri_mesh->_number_vertices; i++) {
        tri_mesh->_vertices[i]._x *= 1.0f / diagonal_length;
        tri_mesh->_vertices[i]._y *= 1.0f / diagonal_length;
        tri_mesh->_vertices[i]._z *= 1.0f / diagonal_length;
    }
}


// Precompute normal to each triangle
void computeTriangleNormals(TriangleMesh* tri_mesh)
{
    int i;

    if (tri_mesh->_triangle_normals) free(tri_mesh->_triangle_normals);

    // Allocate memory for face normals
    tri_mesh->_triangle_normals = (Vector3*)malloc(tri_mesh->_number_triangles * sizeof(Vector3));

    // Go through each face and compute the normal to the triangle
    int nt = tri_mesh->_number_triangles;
    for (i = 0; i < nt; ++i) {
        Triple t = tri_mesh->_triangles[i];
        int v0 = t._v0;
        int v1 = t._v1;
        int v2 = t._v2;

        Vector3 p0 = tri_mesh->_vertices[v0];
        Vector3 p1 = tri_mesh->_vertices[v1];
        Vector3 p2 = tri_mesh->_vertices[v2];

        Vector3 p0p1; sub(p1, p0, &p0p1);
        Vector3 p0p2; sub(p2, p0, &p0p2);
        Vector3 n; computeCrossProduct(p0p1, p0p2, &n); normalize(n, &n);

        tri_mesh->_triangle_normals[i] = n;
    }
}


void computeVertexNormals(TriangleMesh* tri_mesh)
{
    int i;

    computeTriangleNormals(tri_mesh);

    if (tri_mesh->_vertex_normals) free(tri_mesh->_vertex_normals);

    tri_mesh->_vertex_normals = (Vector3*)malloc(tri_mesh->_number_vertices * sizeof(Vector3));
    memset(tri_mesh->_vertex_normals, 0, tri_mesh->_number_vertices * sizeof(Vector3));

    // compute each vertex normal as a weighted average of the adjacent face normals 
    // uniform weight of Area(f)
    int nt = tri_mesh->_number_triangles;
    for (i = 0; i < nt; ++i) {
        Vector3 n_tri = tri_mesh->_triangle_normals[i];

        Triple t = tri_mesh->_triangles[i];
        int v0 = t._v0;
        int v1 = t._v1;
        int v2 = t._v2;
        
        //Calculate weighted normals
        Vector3 p0 = tri_mesh->_vertices[v0];
        Vector3 p1 = tri_mesh->_vertices[v1];
        Vector3 p2 = tri_mesh->_vertices[v2];
        Vector3 p0p1; sub(p1, p0, &p0p1);
        Vector3 p0p2; sub(p2, p0, &p0p2);
        Vector3 fn; computeCrossProduct(p0p1, p0p2, &fn);
        float norm;
        computeNorm(fn,&norm);
        float area = 0.5*norm;
        Vector3 weighted_normal;
        mulAV(area,n_tri, &weighted_normal);

        add(tri_mesh->_vertex_normals[v0], weighted_normal, &(tri_mesh->_vertex_normals[v0]));
        add(tri_mesh->_vertex_normals[v1], weighted_normal, &(tri_mesh->_vertex_normals[v1]));
        add(tri_mesh->_vertex_normals[v2], weighted_normal, &(tri_mesh->_vertex_normals[v2]));
    }

    // normalize
    int nv = tri_mesh->_number_vertices;
    for (i = 0; i < nv; ++i) {
        normalize(tri_mesh->_vertex_normals[i], &(tri_mesh->_vertex_normals[i]));
    }
}


// Access the coordinates of the three vertices of the i-th triangle
void getTriangleVertices(TriangleMesh* tri_mesh, int i, Vector3 coordinates[3])
{
    assert(i >= 0);
    assert(i < tri_mesh->_number_triangles);
    assert(tri_mesh->_triangles);
    assert(tri_mesh->_vertices);

    int v0 = tri_mesh->_triangles[i]._v0;
    int v1 = tri_mesh->_triangles[i]._v1;
    int v2 = tri_mesh->_triangles[i]._v2;

    coordinates[0]._x = tri_mesh->_vertices[v0]._x;
    coordinates[0]._y = tri_mesh->_vertices[v0]._y;
    coordinates[0]._z = tri_mesh->_vertices[v0]._z;

    coordinates[1]._x = tri_mesh->_vertices[v1]._x;
    coordinates[1]._y = tri_mesh->_vertices[v1]._y;
    coordinates[1]._z = tri_mesh->_vertices[v1]._z;

    coordinates[2]._x = tri_mesh->_vertices[v2]._x;
    coordinates[2]._y = tri_mesh->_vertices[v2]._y;
    coordinates[2]._z = tri_mesh->_vertices[v2]._z;
}


// Access the normals to each of the three vertices of the i-th triangle
void getTriangleVertexNormals(TriangleMesh* tri_mesh, int i, Vector3 normals[3])
{
    assert(i >= 0);
    assert(i < tri_mesh->_number_triangles);
    assert(tri_mesh->_triangles);
    assert(tri_mesh->_vertex_normals);

    int v0 = tri_mesh->_triangles[i]._v0;
    int v1 = tri_mesh->_triangles[i]._v1;
    int v2 = tri_mesh->_triangles[i]._v2;

    normals[0]._x = tri_mesh->_vertex_normals[v0]._x;
    normals[0]._y = tri_mesh->_vertex_normals[v0]._y;
    normals[0]._z = tri_mesh->_vertex_normals[v0]._z;

    normals[1]._x = tri_mesh->_vertex_normals[v1]._x;
    normals[1]._y = tri_mesh->_vertex_normals[v1]._y;
    normals[1]._z = tri_mesh->_vertex_normals[v1]._z;

    normals[2]._x = tri_mesh->_vertex_normals[v2]._x;
    normals[2]._y = tri_mesh->_vertex_normals[v2]._y;
    normals[2]._z = tri_mesh->_vertex_normals[v2]._z;
}


// Access the (pre-computed) face normal to the i-th triangle
void getTriangleNormal(TriangleMesh* tri_mesh, int i, Vector3* normal)
{
    assert(i >= 0);
    assert(i < tri_mesh->_number_triangles);
    assert(tri_mesh->_triangle_normals);

    // is it better to return a pointer inside _face_normal ?
    normal->_x = tri_mesh->_triangle_normals[i]._x;
    normal->_y = tri_mesh->_triangle_normals[i]._y;
    normal->_z = tri_mesh->_triangle_normals[i]._z;
}


// Access the (pre-computed) vertex normal for the i-th vertex
void getVertexNormal(TriangleMesh* tri_mesh, int i, Vector3* normal)
{
    assert(i >= 0);
    assert(i < tri_mesh->_number_vertices);
    assert(tri_mesh->_vertex_normals);

    normal->_x = tri_mesh->_vertex_normals[i]._x;
    normal->_y = tri_mesh->_vertex_normals[i]._y;
    normal->_z = tri_mesh->_vertex_normals[i]._z;
}


void getNumberTriangles(TriangleMesh* tri_mesh, int* num_tris)
{
    *num_tris = tri_mesh->_number_triangles;
}


void getNumberVertices(TriangleMesh* tri_mesh, int* num_verts)
{
    *num_verts = tri_mesh->_number_vertices;
}


// Free memory used by the triangle mesh
void freeTriangleMeshStructures(TriangleMesh* tri_mesh)
{
    free(tri_mesh->_vertices);
    free(tri_mesh->_triangles);
    if (tri_mesh->_triangle_normals) free(tri_mesh->_triangle_normals);
    if (tri_mesh->_vertex_normals) free(tri_mesh->_vertex_normals);
    if (tri_mesh->_number_adj_vertices) free(tri_mesh->_number_adj_vertices);
    if (tri_mesh->_adj_vertices) {
        int i;
        int nv = tri_mesh->_number_vertices;
        for (i = 0; i < nv; ++i) free(tri_mesh->_adj_vertices[i]);
        free(tri_mesh->_adj_vertices);
    }

    tri_mesh->_vertices = NULL;
    tri_mesh->_triangles = NULL;
    tri_mesh->_triangle_normals = NULL;
    tri_mesh->_vertex_normals = NULL;
    tri_mesh->_number_adj_vertices = NULL;
    tri_mesh->_adj_vertices = NULL;
}


// Add a neighbor in the adjency list if it is not already there
static void addNeighbor(int* adj, int* nv, int v) {
    int i;
    for (i = 0; i < *nv; ++i) {
        if (adj[i] == v) return;
    }
    adj[*nv] = v;
    (*nv)++;
}


// Build vertex-vertex adjacency map
void computeAdjacencyMap(TriangleMesh* tri_mesh) {
    int nv = tri_mesh->_number_vertices;
    tri_mesh->_number_adj_vertices =
        (int*)malloc(nv * sizeof(int));
    memset(tri_mesh->_number_adj_vertices, 0, nv * sizeof(int));
    tri_mesh->_adj_vertices =
        (int**)malloc(nv * sizeof(int*));
    // pre-allocate
    int i;
    for (i = 0; i < nv; ++i) {
        // average valence is 6, so 24 should be OK as a conservative upper bound
        tri_mesh->_adj_vertices[i] = (int*)malloc(24 * sizeof(int));
    }
    int nt = tri_mesh->_number_triangles;
    for (i = 0; i < nt; ++i) {
        int v0 = tri_mesh->_triangles[i]._v0;
        int v1 = tri_mesh->_triangles[i]._v1;
        int v2 = tri_mesh->_triangles[i]._v2;

        int* nv = &(tri_mesh->_number_adj_vertices[v0]);
        addNeighbor(tri_mesh->_adj_vertices[v0], nv, v1);
        addNeighbor(tri_mesh->_adj_vertices[v0], nv, v2);
        nv = &(tri_mesh->_number_adj_vertices[v1]);
        addNeighbor(tri_mesh->_adj_vertices[v1], nv, v0);
        addNeighbor(tri_mesh->_adj_vertices[v1], nv, v2);
        nv = &(tri_mesh->_number_adj_vertices[v2]);
        addNeighbor(tri_mesh->_adj_vertices[v2], nv, v0);
        addNeighbor(tri_mesh->_adj_vertices[v2], nv, v1);
    }
}


// Get the number of adjacent vertices to vertex i
int getNumberAdjacentVertices(TriangleMesh* tri_mesh, int i) {
    assert(i < tri_mesh->_number_vertices);
    return tri_mesh->_number_adj_vertices[i];
}


// Get the j-th adjacent vertex to vertex i
int getAdjacentVertex(TriangleMesh* tri_mesh, int i, int j) {
    assert(i < tri_mesh->_number_vertices);
    assert(j < tri_mesh->_number_adj_vertices[i]);
    return tri_mesh->_adj_vertices[i][j];
}


// Complete
// Apply one step of heat diffusion.
// Assume that the vertex-vertex adjacency map has been built.
void heatStep(TriangleMesh* tri_mesh) {
    // Complete
    // Try to implement the mesh smoothing method described on p. 40-43 of the slides. 
    // The umbrella operator (p. 42) is sufficient here.

  int num_ver = tri_mesh->_number_vertices;
  Vector3 L_vi; //vi after the execution of Umbrella operator
  Vector3 sumOfAdjacentVertices = {0.f,0.f,0.f}; 
  float lamda = 0.1f;

  for(int i = 0; i < num_ver; ++i){
    int num_neighbors = getNumberAdjacentVertices(tri_mesh, i);
    Vector3 pi = tri_mesh->_vertices[i];

    // Loop through each neighbor
    int j;
    for (j = 0; j < num_neighbors; ++j) {
      // Index in the vertex list of the j-th neighbor
      int vj = getAdjacentVertex(tri_mesh, i, j);
      // Get the coordinates of this vertex
      Vector3 pj = tri_mesh->_vertices[vj];
      add(pj, sumOfAdjacentVertices, &sumOfAdjacentVertices);
    }
    
    //Compute lamda * L_vi
    mulAV(1.f/(float)num_neighbors, sumOfAdjacentVertices, &L_vi);
    sub(L_vi, pi, &L_vi);
    mulAV(lamda, L_vi, &L_vi);

    //Update vi
    add(pi, L_vi, &tri_mesh->_vertices[i]);

    //initialize for computing at next vertex
    mulAV(0.f, sumOfAdjacentVertices, &sumOfAdjacentVertices);
  }
  
  //recompute the normals
  computeTriangleNormals(tri_mesh);
  computeVertexNormals(tri_mesh);
}


// Complete
// Compute the number of connected components and assign a unique component 
// index to each vertex 
void computeConnectedComponents(TriangleMesh* mesh) {
    int i, curr_connected_component=0;

    // Allocate memory and initialize
    if (mesh->_connected_components && mesh->_visited){
        free(mesh->_connected_components);
        free(mesh->_visited);
    }
    mesh->_connected_components = (int*)malloc(mesh->_number_vertices * sizeof(int));
    for(i = 0; i < mesh->_number_vertices; ++i){
        mesh->_connected_components[i] = EMPTY;
    }
    mesh->_visited = (int*)malloc(mesh->_number_vertices * sizeof(int));
    for(i = 0; i < mesh->_number_vertices; ++i){
        mesh->_visited[i] = UNVISITED;
    }
    
    // Traverse the different connected components of the triangle mesh,
    // and assign an index (unique for each component) to the corresponding vertices.
    for(i = 0; i < mesh->_number_vertices; ++i){
        if(DFS(mesh,i,curr_connected_component)) curr_connected_component++;
    }
    
    //printf("A%d ",curr_connected_component);
    //for(i = 0; i < mesh->_number_vertices; ++i){
    //    printf("%d ",mesh->_connected_components[i]);
    //}
}

// If the vertex vidx is adjacent to any unvisited vertex, return 1. Otherwise, return 0.
int DFS(TriangleMesh* mesh, int vidx, int curr_connected_component){
    int adjacent_flag = 0;
    mesh->_visited[vidx] = VISITED;
    if(mesh->_connected_components[vidx] == EMPTY)
        mesh->_connected_components[vidx] = curr_connected_component;
    int num_neighbors = getNumberAdjacentVertices(mesh, vidx);
    for (int j = 0; j < num_neighbors; ++j) {
      int vj = getAdjacentVertex(mesh, vidx, j);
      if( mesh->_visited[vj] == UNVISITED){
          adjacent_flag = 1;
          DFS(mesh,vj,curr_connected_component);
      }
    }
    return adjacent_flag;
}

// Complete 
// Compute the color of a given vertex index based on the connected component 
// that it belongs to
void getComponentColor(TriangleMesh* mesh, int vidx, float* color) {
    // Complete 
    // Return the color (in the argument 'color') of a given vertex (corresponding to the index 'vidx') 
    // based on its component index.
    switch (mesh->_connected_components[vidx]) {
            // We assume there are 3 kinds of color
        case 0:
            color[0] = 1.f;
            color[1] = 0.f;
            color[2] = 0.f;
            break;
        case 1:
            color[0] = 0.f;
            color[1] = 1.f;
            color[2] = 0.f;
            break;
        case 2:
            color[0] = 0.f;
            color[1] = 0.f;
            color[2] = 1.f;
            break;
        default:
            color[0] = 0.f;
            color[1] = 0.f;
            color[2] = 0.f;
            break;
    }
}
