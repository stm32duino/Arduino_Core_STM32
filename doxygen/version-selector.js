// Version selector for the Doxygen pages published under <site>/<version>/doxygen/.
// The list of versions comes from the Mike "versions.json" file at the site root.
document.addEventListener("DOMContentLoaded", async () => {
  const segments = window.location.pathname.split("/").filter(Boolean);
  const index = segments.indexOf("doxygen");
  if (index < 1) {
    return;
  }

  const siteRoot = `${window.location.origin}/${segments.slice(0, index - 1).map(encodeURIComponent).join("/")}`.replace(/\/?$/, "/");
  const currentVersion = decodeURIComponent(segments[index - 1]);
  const pagePath = segments.slice(index).map(encodeURIComponent).join("/")
    + (window.location.pathname.endsWith("/") ? "/" : "");

  let versions;
  try {
    const response = await fetch(`${siteRoot}versions.json`);
    if (!response.ok) {
      return;
    }
    versions = await response.json();
  } catch {
    return;
  }

  const selector = document.getElementById("doc-version");
  const container = document.getElementById("doc-version-selector");
  if (!selector || !container) {
    return;
  }

  for (const entry of versions) {
    for (const name of [...entry.aliases, entry.version]) {
      const option = document.createElement("option");
      option.value = name;
      option.textContent = entry.aliases.includes(name) ? `${name} (${entry.version})` : name;
      option.selected = name === currentVersion;
      selector.add(option);
    }
  }

  selector.addEventListener("change", async () => {
    const version = `${siteRoot}${encodeURIComponent(selector.value)}/`;
    // Keep the same page when the selected version has it, otherwise fall back
    // to the Doxygen home page, then to the documentation home of that version.
    const candidates = [`${version}${pagePath}`, `${version}doxygen/`, version];
    let target = version;
    for (const candidate of candidates) {
      try {
        const response = await fetch(candidate, { method: "HEAD" });
        if (response.ok) {
          target = candidate;
          break;
        }
      } catch {
        break;
      }
    }
    const keepContext = target === candidates[0];
    window.location.assign(`${target}${keepContext ? window.location.search + window.location.hash : ""}`);
  });
  container.style.visibility = "visible";
});
