class Configuration:
    def __init__(self):
        self.wordlists_paths = {
            'default': {"resources/list_of_wordcount_with_lemmatized_in_encyclopaedia_britannica.txt": 1},
            'polish': {"resources/list_of_wordcount_in_wolnelektury_pseudo_lemmatized.txt": 1},
            'english_polish': {
                "resources/list_of_wordcount_with_lemmatized_in_encyclopaedia_britannica.txt": 1,
                "resources/list_of_wordcount_in_wolnelektury_pseudo_lemmatized.txt": 3
            }
        }
        self.stop_words_lists_paths = "resources/stop_words.txt"
        self.config_data = {}

    def get_configuration(self, data: dict):
        wordlist_key = data.get('wordlist', 'default')
        self.config_data['wordlist'] = self.wordlists_paths.get(wordlist_key, self.wordlists_paths['default'])
        self.config_data['stopWordsList'] = self.stop_words_lists_paths
        self.config_data['capitalNamesBoost'] = data['capitalNamesBoost']
        self.config_data['selectivityRatio'] = data['selectivityRatio']
        self.config_data['tags'] = data['tags']
        self.config_data['measure'] = data['measure']
        self.config_data['queryBoostFactor'] = data['queryBoostFactor']
        return self.config_data
