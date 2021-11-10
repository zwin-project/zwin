#include <assert.h>
#include <libxml/parser.h>
#include <stdio.h>
#include <stdlib.h>

#include "test-runner.h"

TEST(validate_xml)
{
  int success;
  const char *wayland_dtd_path = getenv("WAYLAND_DTD_PATH");
  const char *zigen_xml = getenv("ZIGEN_XML");
  assert(wayland_dtd_path && zigen_xml);

  xmlParserCtxtPtr ctx = NULL;
  xmlDocPtr doc = NULL;
  xmlDtdPtr dtd = NULL;
  xmlValidCtxtPtr dtdctx;
  xmlParserInputBufferPtr buffer;

  dtdctx = xmlNewValidCtxt();
  ctx = xmlNewParserCtxt();
  assert(dtdctx && ctx);

  buffer = xmlParserInputBufferCreateFilename(wayland_dtd_path,
                                              XML_CHAR_ENCODING_UTF8);
  assert(buffer);

  dtd = xmlIOParseDTD(NULL, buffer, XML_CHAR_ENCODING_UTF8);
  doc = xmlCtxtReadFile(ctx, zigen_xml, NULL, 0);
  assert(doc && dtd);

  success = xmlValidateDtd(dtdctx, doc, dtd);
  xmlFreeDoc(doc);
  xmlFreeParserCtxt(ctx);
  xmlFreeDtd(dtd);
  xmlFreeValidCtxt(dtdctx);
  assert(success);
}
