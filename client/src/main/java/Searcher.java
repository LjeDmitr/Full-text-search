import com.beust.jcommander.Parameter;
import com.beust.jcommander.Parameters;

@Parameters(commandNames = {"search"}, commandDescription = "Поиск по базе данных csv")
public class Searcher implements Runnable {

    @Parameter(names = {"--query"}, description = "Поисковой запрос")
    private String query;
    @Parameter(names = {"--index"}, description = "Путь до папки с индексами")
    private String indexPath;
    @Parameter(names = "--help", help = true, description = "Help")
    private boolean help = false;

    public void run() {
        Fts.searcher(indexPath, query);
    }

    public boolean Help() {
        return help;
    }
}
