import com.beust.jcommander.Parameter;
import com.beust.jcommander.Parameters;

@Parameters(commandNames = { "index" }, commandDescription = "Индексация по базе данных csv")
public class Indexer implements Runnable {

    public void run() {
        Fts.indexer(csvPath, indexPath);
    }

    @Parameter(names = { "--csv" }, description = "Путь до csv файла")
    private String csvPath;

    @Parameter(names = { "--index" }, description = "Путь до папки с индексами")
    private String indexPath;
}
