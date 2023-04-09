#include <fts-c/Fts.h>
#include <rapidcsv.h>
#include <index/index.hpp>
#include <search/search.hpp>

using namespace std;

string jstring2string(JNIEnv* env, jstring jStr) {
  if (!jStr) {
    return "";
  }

  const jclass stringClass = env->GetObjectClass(jStr);
  const jmethodID getBytes =
      env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
  const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(
      jStr, getBytes, env->NewStringUTF("UTF-8"));

  size_t length = (size_t)env->GetArrayLength(stringJbytes);
  jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

  string result = string((char*)pBytes, length);
  env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

  env->DeleteLocalRef(stringJbytes);
  env->DeleteLocalRef(stringClass);
  return result;
}

JNIEXPORT void JNICALL Java_Fts_indexer(
    JNIEnv* jenv,
    jobject jobj,
    jstring csvPath,
    jstring indexPath) {
  if (jobj == NULL) {
    cout << "Error jobj = NULL" << endl;
    return;
  }

  string csv_path = jstring2string(jenv, csvPath);
  string index_path = jstring2string(jenv, indexPath);

  try {
    rapidcsv::Document book(csv_path);
    vector<string> booksId = book.GetColumn<string>("bookID");
    vector<string> booksName = book.GetColumn<string>("title");

    indexBuilder index_builder;
    for (size_t i = 0; i < 1000; i++) {
      index_builder.add_document(booksId[i], booksName[i]);
    }

    textIndexWriter::documentsCreate(index_path, index_builder);
    textIndexWriter::write(index_path, index_builder);
    book.Clear();
  } catch (exception const& e) {
    cerr << "Error, " << e.what() << endl;
  }
}

JNIEXPORT void JNICALL Java_Fts_searcher(
    JNIEnv* jenv,
    jobject jobj,
    jstring indexPath,
    jstring jquery) {
  if (jobj == NULL) {
    cout << "Error jobj = NULL" << endl;
    return;
  }
  string query = jstring2string(jenv, jquery);
  string index_path = jstring2string(jenv, indexPath);

  SearchIndex book_search;
  book_search.search(query, index_path);
  vector<string> docsNames = IndexAccessor::allDocNames(index_path);
  for (size_t i = 0; i < docsNames.size(); i++) {
    book_search.score(docsNames[i]);
  }

  cout << "id"
       << "\t"
       << "score"
       << "\t"
       << "text" << endl;
  IndexAccessor index_access;
  vector<pair<string, double>> result = book_search.getSearchResult();
  for (size_t i = 0; i < result.size(); i++) {
    index_access.readDoc(result[i].first);
    cout << result[i].first << "\t" << result[i].second << "\t"
         << index_access.getDocText() << endl;
  }
}