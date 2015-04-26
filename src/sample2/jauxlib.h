// ************** FROM lauxlib.h **************

typedef struct luaL_Buffer {
  char *b;  /* buffer address */
  size_t size;  /* buffer size */
  size_t n;  /* number of characters in buffer */
  lua_State *L;
  char initb[LUAL_BUFFERSIZE];  /* initial buffer */
} luaL_Buffer;


#define luaL_addsize(B,s)	((B)->n += (s))

// ************** FROM lauxlib.c **************

/* value at a non-valid index */
#define NONVALIDVALUE		cast(TValue *, luaO_nilobject)

/* corresponding test */
#define isvalid(o)	((o) != luaO_nilobject)

/* test for pseudo index */
#define ispseudo(i)		((i) <= LUA_REGISTRYINDEX)

/* test for upvalue */
#define isupvalue(i)		((i) < LUA_REGISTRYINDEX)

/* test for valid but not pseudo index */
#define isstackindex(i, o)	(isvalid(o) && !ispseudo(i))

#define api_checkvalidindex(o)  api_check(isvalid(o), "invalid index")

#define api_checkstackindex(i, o)  \
	api_check(isstackindex(i, o), "index not in the stack")


LUALIB_API void luaL_where (lua_State *L, int level) {
  lua_Debug ar;
  if (lua_getstack(L, level, &ar)) {  /* check function at level */
    lua_getinfo(L, "Sl", &ar);  /* get info about it */
    if (ar.currentline > 0) {  /* is there info? */
      lua_pushfstring(L, "%s:%d: ", ar.short_src, ar.currentline);
      return;
    }
  }
  lua_pushliteral(L, "");  /* else, no information available... */
}


LUALIB_API int luaL_error (lua_State *L, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  luaL_where(L, 1);
  lua_pushvfstring(L, fmt, argp);
  va_end(argp);
  lua_concat(L, 2);
  return lua_error(L);
}


/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

/*
** check whether buffer is using a userdata on the stack as a temporary
** buffer
*/
#define buffonstack(B)	((B)->b != (B)->initb)


/*
** returns a pointer to a free area with at least 'sz' bytes
*/
LUALIB_API char *luaL_prepbuffsize (luaL_Buffer *B, size_t sz) {
  lua_State *L = B->L;
  if (B->size - B->n < sz) {  /* not enough space? */
    char *newbuff;
    size_t newsize = B->size * 2;  /* double buffer size */
    if (newsize - B->n < sz)  /* not big enough? */
      newsize = B->n + sz;
    if (newsize < B->n || newsize - B->n < sz)
      luaL_error(L, "buffer too large");
    /* create larger buffer */
    newbuff = (char *)lua_newuserdata(L, newsize * sizeof(char));
    /* move content to new buffer */
    memcpy(newbuff, B->b, B->n * sizeof(char));
    if (buffonstack(B))
      lua_remove(L, -2);  /* remove old buffer */
    B->b = newbuff;
    B->size = newsize;
  }
  return &B->b[B->n];
}


LUALIB_API void luaL_addlstring (luaL_Buffer *B, const char *s, size_t l) {
  char *b = luaL_prepbuffsize(B, l);
  memcpy(b, s, l * sizeof(char));
  luaL_addsize(B, l);
}


LUALIB_API void luaL_addstring (luaL_Buffer *B, const char *s) {
  luaL_addlstring(B, s, strlen(s));
}


LUALIB_API void luaL_pushresult (luaL_Buffer *B) {
  lua_State *L = B->L;
  lua_pushlstring(L, B->b, B->n);
  if (buffonstack(B))
    lua_remove(L, -2);  /* remove old buffer */
}


LUALIB_API void luaL_pushresultsize (luaL_Buffer *B, size_t sz) {
  luaL_addsize(B, sz);
  luaL_pushresult(B);
}


LUALIB_API void luaL_addvalue (luaL_Buffer *B) {
  lua_State *L = B->L;
  size_t l;
  const char *s = lua_tolstring(L, -1, &l);
  if (buffonstack(B))
    lua_insert(L, -2);  /* put value below buffer */
  luaL_addlstring(B, s, l);
  lua_remove(L, (buffonstack(B)) ? -2 : -1);  /* remove value */
}


LUALIB_API void luaL_buffinit (lua_State *L, luaL_Buffer *B) {
  B->L = L;
  B->b = B->initb;
  B->n = 0;
  B->size = LUAL_BUFFERSIZE;
}


LUALIB_API char *luaL_buffinitsize (lua_State *L, luaL_Buffer *B, size_t sz) {
  luaL_buffinit(L, B);
  return luaL_prepbuffsize(B, sz);
}

/* }====================================================== */
