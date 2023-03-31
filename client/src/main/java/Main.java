import com.beust.jcommander.JCommander;

import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        try {
            setLibraryPath();

            Map<String, Runnable> map = new HashMap<String, Runnable>();
            Indexer indexer = new Indexer();
            Searcher searcher = new Searcher();
            map.put("index", indexer);
            map.put("search", searcher);

            JCommander jc = new JCommander();
            jc.addCommand(indexer);
            jc.addCommand(searcher);
            jc.parse(args);

            String name = jc.getParsedCommand();
            map.get(name).run();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private static void setLibraryPath() throws Exception {
        System.setProperty("java.library.path", "/home/ljedmitry/VsCode/fts-LjeDmitr/build/debug/src/fts-c");

        Field sysPathsField = ClassLoader.class.getDeclaredField("sys_paths");
        sysPathsField.setAccessible(true);
        sysPathsField.set(null, null);
    }
}
