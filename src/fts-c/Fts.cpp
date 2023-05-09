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
    vector<size_t> booksId = book.GetColumn<size_t>("bookID");
    vector<string> booksName = book.GetColumn<string>("title");

    indexBuilder index_builder;
    for (size_t i = 0; i < 1000; i++) {
      index_builder.add_document(booksId[i], booksName[i]);
    }

    BinaryIndexWriter::write(index_path, index_builder);
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
  cout << "score"
       << "\t"
       << "title" << endl;
  vector<pair<string, double>> result = book_search.getSearchResult();
  for (size_t i = 0; i < result.size(); i++) {
    cout << result[i].second << "\t" << result[i].first << endl;
  }
}