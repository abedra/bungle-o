#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

char *search(char *q, xmlDocPtr doc, xmlXPathContextPtr xpathCtx) {
  xmlNodeSetPtr nodes;
  xmlNodePtr cur;
  xmlXPathObjectPtr xpathObj;

  int i, size;
  char *result;

  xpathObj = xmlXPathEvalExpression(q, xpathCtx);
  if (xpathObj == NULL) {
    fprintf(stderr, "Error: unable to evaluate XPath expression\n");
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    return;
  }

  nodes = xpathObj->nodesetval;
  size = (nodes) ? nodes->nodeNr : 0;

  if (size == 1) {
    printf("node %s\n", xmlNodeGetContent(nodes->nodeTab[0]));
  } else {
    for (i = 0; i < size; i++) {
      cur = nodes->nodeTab[i];
      printf("node %s\n", xmlNodeGetContent(cur));
    }
  }

  xmlXPathFreeObject(xpathObj);
  result = "";
  return result;
}

int main(int argc, char **argv)
{
  xmlDocPtr doc;
  xmlXPathContextPtr xpathCtx;
  
  char *filename;

  filename = argv[1];

  doc = xmlParseFile(filename);
  if (doc == NULL) {
    fprintf(stderr, "Error: unable to parse file %s \n", filename);
    return 1;
  }

  xpathCtx = xmlXPathNewContext(doc);
  if (xpathCtx == NULL) {
    fprintf(stderr, "Error: unable to create new XPath context\n");
    xmlFreeDoc(doc);
    return 1;
  }

  search("/notice/error/class", doc, xpathCtx);
  search("/notice/error/message", doc, xpathCtx);

  xmlXPathFreeContext(xpathCtx);
  xmlFreeDoc(doc);

  return 0;
}
