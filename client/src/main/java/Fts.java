public class Fts {
    static {
        System.loadLibrary("fts-c");
    }

    public static native void indexer(String csvPath, String indexPath);
    public static native void searcher(String indexPath, String query);
}
