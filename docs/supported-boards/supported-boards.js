(function () {
  function setupBoardSearch() {
    var search = document.getElementById("supported-boards-search");
    if (!search || search.dataset.initialized === "true") {
      return;
    }

    search.dataset.initialized = "true";
    var count = document.getElementById("supported-boards-count");
    var content = search.closest(".md-content") || document;
    var sections = [];

    content.querySelectorAll("table").forEach(function (table) {
      var body = table.tBodies[0];
      var wrapper = table.closest(".md-typeset__scrollwrap");
      var heading = wrapper && wrapper.previousElementSibling;
      if (body && heading && heading.tagName === "H3") {
        sections.push({
          heading: heading,
          table: wrapper,
          sectionText: heading.textContent.toLocaleLowerCase(),
          rows: Array.from(body.rows),
        });
      }
    });

    function filterRows() {
      var query = search.value.trim().toLocaleLowerCase();
      var queryWords = query.split(/\s+/).filter(Boolean);
      var visibleRows = 0;

      sections.forEach(function (section) {
        var sectionMatches = 0;
        section.rows.forEach(function (row) {
          var searchableText = (section.sectionText + " " + row.textContent).toLocaleLowerCase();
          var matches = queryWords.every(function (word) {
            return searchableText.includes(word);
          });
          row.hidden = !matches;
          sectionMatches += matches ? 1 : 0;
        });
        section.heading.hidden = sectionMatches === 0;
        section.table.hidden = sectionMatches === 0;
        visibleRows += sectionMatches;
      });

      search.setAttribute("aria-label", visibleRows + " matching supported boards");
      if (count) {
        count.textContent = visibleRows + (visibleRows === 1 ? " board" : " boards") + " found";
      }
    }

    search.addEventListener("input", filterRows);
    search.addEventListener("search", filterRows);
    filterRows();
  }

  function initialize() {
    setupBoardSearch();
  }

  if (typeof document$ !== "undefined") {
    document$.subscribe(initialize);
  }
  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", initialize);
  } else {
    initialize();
  }
})();
