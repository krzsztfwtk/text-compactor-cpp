from flask import Flask
from webui.route_handler import RouteHandler

class WebApp:
    def __init__(self):
        self.app = Flask(__name__)
        self.route_handler = RouteHandler()

        self.app.add_url_rule('/', 'home', self.route_handler.home)
        self.app.add_url_rule('/text_compactor', 'text_compactor', self.route_handler.text_compactor)
        self.app.add_url_rule('/insight_search', 'insight_search', self.route_handler.insight_search)
        self.app.add_url_rule('/compact_text', 'compact_text', self.route_handler.compact_text, methods=['POST'])

    def run(self):
        self.app.run(debug=True)


