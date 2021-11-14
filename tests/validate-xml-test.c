#include <assert.h>
#include <libxml/parser.h>
#include <stdio.h>
#include <stdlib.h>

#include "test-runner.h"

void validate_xml(const char *xml_path)
{
  int success;
  const char *wayland_dtd_path = getenv("WAYLAND_DTD_PATH");
  assert(wayland_dtd_path && xml_path);

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
  doc = xmlCtxtReadFile(ctx, xml_path, NULL, 0);
  assert(doc && dtd);

  success = xmlValidateDtd(dtdctx, doc, dtd);
  xmlFreeDoc(doc);
  xmlFreeParserCtxt(ctx);
  xmlFreeDtd(dtd);
  xmlFreeValidCtxt(dtdctx);
  assert(success);
}

TEST(validate_zigen_xml)
{
  const char *zigen_xml = getenv("ZIGEN_XML");
  validate_xml(zigen_xml);
}

TEST(validate_zigen_shell_xml)
{
  const char *zigen_shell_xml = getenv("ZIGEN_SHELL_XML");
  validate_xml(zigen_shell_xml);
}

TEST(validate_zigen_opengl_xml)
{
  const char *zigen_opengl_xml = getenv("ZIGEN_OPENGL_XML");
  validate_xml(zigen_opengl_xml);
}
