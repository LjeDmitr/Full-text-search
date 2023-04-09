import com.beust.jcommander.Parameter;
import com.beust.jcommander.Parameters;

@Parameters(commandNames = {"index"}, commandDescription = "Индексация по базе данных csv")
public class Indexer implements Runnable {

    @Parameter(names = {"--csv"}, description = "Путь до csv файла", required = true)
    private String csvPath;
    @Parameter(names = {"--index"}, description = "Путь до папки с индексами", required = true)
    private String indexPath;
    @Parameter(names = "--help", help = true, description = "Help")
    private boolean help = false;

    public void run() {
        Fts.indexer(csvPath, indexPath);
    }

    public boolean Help() {
        return help;
    }
}
