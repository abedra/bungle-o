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

  result = xmlNodeGetContent(nodes->nodeTab[0]);

  xmlXPathFreeObject(xpathObj);

  return result;
}

int main(int argc, char **argv)
{
  xmlDocPtr doc;
  xmlXPathContextPtr xpathCtx;
  
  char *filename, *class, *message;

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

  class = search("/notice/error/class", doc, xpathCtx);
  message = search("/notice/error/message", doc, xpathCtx);

  printf("class: %s\n", class);
  printf("message: %s\n", message);

  xmlXPathFreeContext(xpathCtx);
  xmlFreeDoc(doc);

  return 0;
}
